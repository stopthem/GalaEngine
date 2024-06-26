#include "ECS.h"

#include <algorithm>

#include "../Components/NameComponent.h"
#include "../Components/UUIDComponent.h"
#include "../Logger/Logger.h"

namespace gala
{
    int IComponent::NextId = 0;

    Entity::Entity(const int id, class Registry* registry)
        : Id(id), Registry(registry)
    {
    }

    void Entity::Kill() const
    {
        Registry->KillEntity(*this);
    }

    bool Entity::IsValid() const
    {
        return Registry->IsEntityValid(*this);
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
        if (std::ranges::find(SystemEntities, entity) != SystemEntities.end())
        {
            return;
        }

        // If not push it.
        SystemEntities.push_back(entity);
    }

    void System::RemoveEntityFromSystem(Entity entity)
    {
        // Remove all entities that matches the predicate. Entities will be unique so no problem.
        std::erase_if(SystemEntities
                      , [&entity](const Entity otherEntity)
                      {
                          return entity == otherEntity;
                      });
    }

    void System::ForEachSystemEntity(const std::function<void(Entity)>& callback)
    {
        std::ranges::for_each(SystemEntities, callback);
    }

    Entity Registry::CreateEntity()
    {
        int entityId;
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

        // Add it to the all entities set
        AllEntities.emplace(entity);

        // Add a "UuidComponent" to entity because all entities have uuid
        AddComponent<UuidComponent>(entity);

        // Add a "NameComponent" to entity because all entities have name
        AddComponent<NameComponent>(entity, std::format("Entity with id: {}", entityId));

        return entity;
    }

    void Registry::KillEntity(const Entity entity)
    {
        EntitiesToBeKilled.emplace(entity);
    }

    void Registry::ForEachEntity(const std::function<void(Entity)>& callback)
    {
        std::ranges::for_each(AllEntities, callback);
    }

    void Registry::AddEntityTag(Entity entity, const std::string& tag)
    {
        TagPerEntity.emplace(entity.GetId(), tag);
        EntityPerTag.emplace(tag, entity);
    }

    bool Registry::EntityHasTag(const Entity entity, const std::string& tag) const
    {
        if (!TagPerEntity.contains(entity.GetId()))
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
        if (!EntityPerGroup.contains(group))
        {
            return false;
        }

        const auto groupEntities = EntityPerGroup.at(group);
        return groupEntities.contains(entity);
    }

    std::vector<Entity> Registry::GetEntitiesByGroup(const std::string& group) const
    {
        if (EntityPerGroup.contains(group))
        {
            std::set<Entity> foundEntityGroup = EntityPerGroup.at(group);
            return {foundEntityGroup.begin(), foundEntityGroup.end()};
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

            // Add if entity isn't already added to system
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
        // Process entities to be killed.
        for (Entity entityToBeKilled : EntitiesToBeKilled)
        {
            AllEntities.erase(entityToBeKilled);

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
}
