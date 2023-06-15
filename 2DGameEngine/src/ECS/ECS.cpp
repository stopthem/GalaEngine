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

void Entity::AddTag(const std::string& tag) const
{
	Registry->AddEntityTag(*this, tag);
}

bool Entity::HasTag(const std::string& tag) const
{
	return Registry->EntityHasTag(*this, tag);
}

void Entity::RemoveTag() const
{
	Registry->RemoveEntityTag(*this);
}

void Entity::AddToGroup(const std::string& group) const
{
	Registry->AddEntityGroup(*this, group);
}

bool Entity::InGroup(const std::string& group) const
{
	return Registry->IsEntityInGroup(*this, group);
}

void Entity::RemoveFromGroup() const
{
	Registry->RemoveEntityGroup(*this);
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

void Registry::AddEntityTag(Entity entity, const std::string& tag)
{
	TagPerEntity.emplace(entity.GetId(), tag);
	EntityPerTag.emplace(tag, entity);
}

bool Registry::EntityHasTag(const Entity entity, const std::string& tag) const
{
	if (TagPerEntity.find(entity.GetId()) == TagPerEntity.end())
	{
		return false;
	}

	return TagPerEntity.at(entity.GetId()) == tag;
}

Entity Registry::GetEntityByTag(const std::string& tag) const
{
	return EntityPerTag.at(tag);
}

void Registry::RemoveEntityTag(const Entity entity)
{
	if (const auto foundIterator = TagPerEntity.find(entity.GetId()); foundIterator != TagPerEntity.end())
	{
		EntityPerTag.erase(foundIterator->second);
		TagPerEntity.erase(foundIterator);
	}
}

void Registry::AddEntityGroup(const Entity entity, const std::string& group)
{
	GroupPerEntity.emplace(entity.GetId(), group);
	EntityPerGroup.emplace(group, std::set<Entity>());
	EntityPerGroup[group].emplace(entity);
}

bool Registry::IsEntityInGroup(const Entity entity, const std::string& group) const
{
	auto groupEntities = EntityPerGroup.at(group);
	return groupEntities.find(entity) != groupEntities.end();
}

std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
{
	if (EntityPerGroup.find(group) != EntityPerGroup.end())
	{
		std::set<Entity> foundEntityGroup = EntityPerGroup.at(group);
		return{ foundEntityGroup.begin(),foundEntityGroup.end() };
	}

	return {};
}

void Registry::RemoveEntityGroup(const Entity entity)
{
	if (const auto foundIterator = GroupPerEntity.find(entity.GetId()); foundIterator != GroupPerEntity.end())
	{
		EntityPerGroup[foundIterator->second].erase(entity);
		GroupPerEntity.erase(foundIterator);
	}
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

		RemoveEntityGroup(entityToBeKilled);

		RemoveEntityTag(entityToBeKilled);

		FreeIds.push_back(entityToBeKilled.GetId());

		EntityComponentSignatures[entityToBeKilled.GetId()].reset();

		for (const std::shared_ptr<IPool>& componentPool : ComponentPools)
		{
			if (!componentPool)
			{
				continue;
			}
			componentPool->RemoveEntityFromPool(entityToBeKilled.GetId());
		}
	}

	EntitiesToBeKilled.clear();

}
