#include "ECS.h"
#include "../Logger/Logger.h"

int IComponent::NextId = 0;

Entity::Entity(const int id)
	:Id(id)
{
}

void System::AddEntityToSystem(const Entity entity)
{
	// Does entities contain given entity ?
	if (std::find(Entities.begin(), Entities.end(), entity) == Entities.end())
	{
		return;
	}

	// If not push it.
	Entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
	Entities.erase(std::remove_if(Entities.begin(), Entities.end()
		, [&entity](const Entity otherEntity)
		{
			return entity == otherEntity;
		})
		, Entities.end());
}

Entity Registry::CreateEntity()
{
	const int entityId = NumEntities++;

	if (EntityComponentSignatures.size() <= static_cast<unsigned>(NumEntities))
	{
		EntityComponentSignatures.resize(NumEntities);
	}

	const Entity entity(entityId);

	EntitiesToBeAdded.insert(entity);

	// Make sure the entityComponentSignatures vector can accomodate the new entity.
	if (static_cast<unsigned>(entityId) >= EntityComponentSignatures.size())
	{
		EntityComponentSignatures.reserve(entityId + 1);
	}

	Logger::Log("Entity created with id " + std::to_string(entityId));

	return entity;
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

void Registry::Update()
{
	for (const Entity entity : EntitiesToBeAdded)
	{
		AddEntityToSystems(entity);
	}

	EntitiesToBeAdded.clear();

	//TODO: kill entities in EntitiesToBeKilled.
}
