#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::NextId = 0;

Entity::Entity(const int id, class Registry* registry)
	:Id(id), Registry(registry)
{
}

void Entity::Kill() const
{
	Registry->KillEntity(*this);
}

void System::AddEntityToSystem(const Entity entity)
{
	// Does entities contain given entity ?
	if (std::find(Entities.begin(), Entities.end(), entity) != Entities.end())
	{
		return;
	}

	// If not push it.
	Entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
	// Remove all entities that matches the predicate. Entities will be unique so no problem.
	Entities.erase(std::remove_if(Entities.begin(), Entities.end()
		, [&entity](const Entity otherEntity)
		{
			return entity == otherEntity;
		})
		, Entities.end());
}

Entity Registry::CreateEntity()
{
	int entityId = 0;
	if (FreeIds.empty())
	{
		entityId = NumEntities++;

		// Make sure the entityComponentSignatures vector can accomodate the new entity.
		if (EntityComponentSignatures.size() <= static_cast<unsigned>(NumEntities))
		{
			EntityComponentSignatures.resize(NumEntities);
		}
	}
	else
	{
		entityId = FreeIds.front();
		FreeIds.pop_front();
	}


	const Entity entity(entityId, this);

	EntitiesToBeAdded.insert(entity);

	return entity;
}

void Registry::KillEntity(const Entity entity)
{
	EntitiesToBeKilled.insert(entity);
}

void Registry::AddEntityToSystems(const Entity entity)
{
	for (auto& [typeIndex, system] : Systems)
	{
		const Signature systemSignature = system->GetSignature();

		const Signature entityComponentSignature = EntityComponentSignatures[entity.GetId()];

		if ((entityComponentSignature & systemSignature) == systemSignature)
		{
			system->AddEntityToSystem(entity);
		}
	}
}

void Registry::RemoveEntityFromSystems(const Entity entity)
{
	for (auto& [typeIndex, system] : Systems)
	{
		system->RemoveEntityFromSystem(entity);
	}
}

void Registry::Update()
{
	// Process entities to be added.
	for (const Entity entity : EntitiesToBeAdded)
	{
		AddEntityToSystems(entity);
	}

	EntitiesToBeAdded.clear();

	// Process entities to be killed.
	for (Entity entityToBeKilled : EntitiesToBeKilled)
	{
		RemoveEntityFromSystems(entityToBeKilled);

		FreeIds.push_back(entityToBeKilled.GetId());

		EntityComponentSignatures[entityToBeKilled.GetId()].reset();
	}

	EntitiesToBeKilled.clear();
}
