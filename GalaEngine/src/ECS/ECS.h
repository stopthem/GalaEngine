#pragma once

#include "../Core/UUID.h"
#include "../Components/UUIDComponent.h"
#include <vector>
#include <bitset>
#include <deque>
#include <functional>
#include <memory>
#include <typeindex>
#include <set>
#include <string>

#include "../Logger/Logger.h"

namespace gala
{
    constexpr char TAG_PLAYER[] = "Player";

    constexpr char GROUP_FRIENDLY[] = "FriendlyGroup";
    constexpr char GROUP_ENEMY[] = "EnemyGroup";
    constexpr char GROUP_PROJECTILE[] = "ProjectileGroup";
    constexpr char GROUP_TILEMAP[] = "TileMapGroup";
    constexpr char GROUP_OBSTACLE[] = "ObstacleGroup";

    // We hold this value because we use a bit set for if entity has a component.
    constexpr unsigned int MAX_COMPONENTS = 32;

    // We use a bitset (1-0)s to keep track of which components an entity has,
    // and also helps keep track of which entities a system is interested in.
    typedef std::bitset<MAX_COMPONENTS> Signature;

    /*
 * IComponent
 *
 * Wrapper class for IComponent.
 */
    struct IComponent
    {
    protected:
        static int NextId;
    };

    /*
 * Component
 *
 * Only provides a unique id for component types.
 */
    template <typename T>
    class Component : public IComponent
    {
    public:
        // Returns the unique id of Component<TComponent>.
        static int GetId()
        {
            static int id = NextId++;
            return id;
        }
    };

    class Registry;
    /*
 * Entity
 *
 * Has no functionality and holds only its id.
 */
    class Entity
    {
    public:
        explicit Entity(int id, Registry* registry);

        Entity(const Entity& otherEntity) = default;

        Entity() = default;

#pragma region Uuid

    public:
        [[nodiscard]] int GetId() const { return Id; }

        [[nodiscard]] Uuid GetUuid() const
        {
            return GetComponent<UuidComponent>().Uuid;
        }
#pragma endregion

    private:
        int Id = 0;

    public:
        Registry* Registry = nullptr;

    public:
        void Kill() const;

        [[nodiscard]] bool IsValid() const;

#pragma region Tags and Groups

    public:
        void AddTag(const std::string& tag) const;

        [[nodiscard]] bool HasTag(const std::string& tag) const;

        void RemoveTag() const;

        void AddToGroup(const std::string& group) const;

        [[nodiscard]] bool InGroup(const std::string& group) const;

        void RemoveFromGroup() const;
#pragma endregion

#pragma region Component

    public:
        template <typename TComponent, typename... TComponentArgs>
        TComponent& AddComponent(TComponentArgs&&... componentArgs);

        template <typename TComponent>
        void RemoveComponent() const;

        template <typename TComponent>
        [[nodiscard]] bool HasComponent() const;

        // Returns if component exists and if found, sticks it in out_component.
        // Note : returns READ-ONLY TComponent.
        template <typename TComponent>
        [[nodiscard]] bool TryGetComponent(TComponent& outComponent);

        template <typename TComponent>
        [[nodiscard]] TComponent& GetComponent() const;
#pragma endregion

#pragma region Operator Overloads

    public:
        Entity& operator=(const Entity& otherEntity) = default;

        bool operator==(const Entity& otherEntity) const
        {
            return GetUuid() == otherEntity.GetUuid();
        }

        bool operator!=(const Entity& otherEntity) const
        {
            return GetUuid() != otherEntity.GetUuid();
        }

        bool operator<(const Entity& otherEntity) const
        {
            return GetId() < otherEntity.GetId();
        }
#pragma endregion
    };

    /*
* System
*
* The system process entities that contain specific signature.
*/
    class System
    {
    public:
        System() = default;
        virtual ~System() = default;

    public:
        // Define the component type TComponent that entities must have to be 
        // considered by the system.
        template <typename TComponent>
        void RequireComponent();

    public:
        void AddEntityToSystem(Entity entity);

        void RemoveEntityFromSystem(Entity entity);

        void ForEachSystemEntity(const std::function<void(Entity)>& callback);

        [[nodiscard]] std::vector<Entity> GetSystemEntities() const { return SystemEntities; }

    private:
        std::vector<Entity> SystemEntities;

    public:
        [[nodiscard]] Signature GetSignature() const { return ComponentSignature; }

    private:
        Signature ComponentSignature;

    public:
        virtual void OnSystemRemoved()
        {
        }
    };

    template <typename TComponent>
    void System::RequireComponent()
    {
        const int componentId = Component<TComponent>().GetId();

        ComponentSignature.set(componentId);
    }

    /*
 * IPool
 *
 * Wrapper class for Pool<T>.
 */
    class IPool
    {
    public:
        virtual ~IPool() = default;

    public:
        virtual void RemoveEntityFromPool(uint32_t entityId) = 0;
    };

    /*
* Pool
*
* A pool is just a vector(contiguous data) of objects of type TComponent.
*/
    template <typename TPool>
    class Pool final : public IPool
    {
    public:
        Pool() = default;
        ~Pool() override = default;

    public:
        void RemoveEntityFromPool(const uint32_t entityId) override
        {
            // Did we not find the index of the given entityId ?
            if (std::ranges::find(EntityIdToIndex, entityId) == EntityIdToIndex.end())
            {
                return;
            }

            Remove(entityId);
        }

    private:
        std::vector<TPool> Data;

        std::vector<uint32_t> EntityIdToIndex;

        std::vector<uint32_t> IndexToEntity;

    public:
        [[nodiscard]] bool IsEmpty() const { return Data.size() == 0; }

        [[nodiscard]] int GetSize() const { return Data.size(); }

        void Clear()
        {
            Data.clear();

            EntityIdToIndex.clear();

            IndexToEntity.clear();
        }

        void Set(const uint32_t entityId, TPool object)
        {
            const uint32_t index = Data.size();

            // We resize because we don't pop or erase this vector.
            if (EntityIdToIndex.size() < entityId + 1)
            {
                EntityIdToIndex.resize((entityId + 1) * 2);
            }

            EntityIdToIndex[entityId] = index;

            // This vector and Data vector's size is same.
            // With that, we can push back safely.
            IndexToEntity.push_back(entityId);

            Data.push_back(object);
        }

        void Remove(const uint32_t entityId)
        {
            // Did we not found the given entityId in our EntityIdToIndex vector ?
            if (std::ranges::find(EntityIdToIndex, entityId) == EntityIdToIndex.end())
            {
                return;
            }

            const uint32_t deletedIndex = EntityIdToIndex[entityId];

            const uint32_t indexOfLast = Data.size() - 1;

            const uint32_t entityIdOfLastElement = IndexToEntity[indexOfLast];

            // Change deleted index component to last component, so we can pop from back.
            Data[deletedIndex] = Data[indexOfLast];

            // Change last index of EntityIdToIndex to deleted index because we will do opposite on IndexToEntity.
            EntityIdToIndex[entityIdOfLastElement] = deletedIndex;

            IndexToEntity[deletedIndex] = entityIdOfLastElement;

            // This vector and Data vector's size is same.
            // With that, we can pop back safely.
            IndexToEntity.pop_back();

            Data.pop_back();
        }

        TPool& Get(const uint32_t index) { return Data[EntityIdToIndex[index]]; }

        TPool& operator[](const uint32_t index) { return Get(index); }
    };

    /*
* Registry
*
* The registry manages the creation and destruction of entities, as well as
* adding system and adding components to entities.
*/
    class Registry
    {
    private:
        // Keep track of how many entities were added to the scene.
        int NumEntities = 0;

    public:
        Registry() = default;

    private:
        // Set of entities that are flagged to be removed in the next registry update.
        std::set<Entity> EntitiesToBeKilled;

        // List of free entity ids that were previously deleted.
        std::deque<int> FreeIds;

        // Set of all entities
        std::set<Entity> AllEntities;

    public:
        [[nodiscard]] Entity CreateEntity();

        void KillEntity(Entity entity);

        [[nodiscard]] std::set<Entity> GetAllEntities() const { return AllEntities; }

        void ForEachEntity(const std::function<void(Entity)>& callback);

#pragma region Tags and Groups

    private:
        std::unordered_map<std::string, Entity> EntityPerTag;
        std::unordered_map<int, std::string> TagPerEntity;

        std::unordered_map<std::string, std::set<Entity>> EntityPerGroup;
        std::unordered_map<int, std::string> GroupPerEntity;

    public:
        // I'm aware like course teacher that most of these functions lack validation.
        // Look at readme.md to why I don't plan to fix it.

        void AddEntityTag(Entity entity, const std::string& tag);

        [[nodiscard]] bool EntityHasTag(Entity entity, const std::string& tag) const;

        [[nodiscard]] Entity GetEntityByTag(const std::string& tag) const;

        void RemoveEntityTag(Entity entity);

        void AddEntityGroup(Entity entity, const std::string& group);

        [[nodiscard]] bool IsEntityInGroup(Entity entity, const std::string& group) const;

        [[nodiscard]] std::vector<Entity> GetEntitiesByGroup(const std::string& group) const;

        void RemoveEntityGroup(Entity entity);
#pragma endregion

#pragma region Component

    private:
        // Vector of component pools, each pool contains all the data for a certain component t.
        // Vector index = component id.
        // Pool index = entity id.
        std::vector<std::shared_ptr<IPool>> ComponentPools;

        // Vector of component signatures per entity, saying which component is turned "on" for the entity.
        // Vector index = entity id.
        std::vector<Signature> EntityComponentSignatures;

    public:
        template <typename TComponent, typename... TComponentArgs>
        TComponent& AddComponent(Entity entity, TComponentArgs... componentArgs);

        template <typename TComponent>
        void RemoveComponent(Entity entity);

        template <typename TComponent>
        [[nodiscard]] bool HasComponent(Entity entity) const;

        template <typename TComponent>
        [[nodiscard]] TComponent& GetComponent(Entity entity) const;

#pragma endregion

#pragma region System

    private:
        // Map index = system id.
        std::unordered_map<std::type_index, std::shared_ptr<System>> Systems;

    public:
        template <typename TSystem, typename... TSystemArgs>
        void AddSystem(TSystemArgs&&... systemArgs);

        template <typename TSystem>
        void RemoveSystem();

        template <typename TSystem>
        [[nodiscard]] bool HasSystem() const;

        template <typename TSystem>
        [[nodiscard]] TSystem& GetSystem() const;

        // Checks the component signature of an entity and add the entity to the systems
        // that are interested in it.
        void AddEntityToSystems(Entity entity);

        // Checks the component signature of an entity and remove the entity to the systems
        // that are interested in it.
        void RemoveEntityFromSystems(Entity entity);
#pragma endregion

    public:
        void Update();

        [[nodiscard]] bool IsEntityValid(const Entity entity) const
        {
            return AllEntities.contains(entity);
        }
    };

#pragma region Registry Component Template Functions

    template <typename TComponent, typename... TComponentArgs>
    TComponent& Registry::AddComponent(const Entity entity, TComponentArgs... componentArgs)
    {
        const int componentId = Component<TComponent>::GetId();
        const int entityId = entity.GetId();

        // If component id is greater than componentPools.size, resize it and null the new object.
        if (static_cast<unsigned>(componentId) >= ComponentPools.size())
        {
            ComponentPools.resize(componentId + 1, nullptr);
        }

        // If we still don't have a pool for that component type create one.
        if (!ComponentPools[componentId])
        {
            std::shared_ptr<Pool<TComponent>> newComponentPool = std::make_shared<Pool<TComponent>>();
            ComponentPools[componentId] = newComponentPool;
        }

        // Fetch the corresponding type of pool from component pools.
        std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(ComponentPools[componentId]);

        // Create the new component with the given multiple componentArgs.
        TComponent newComponent(std::forward<TComponentArgs>(componentArgs)...);

        // Add the new component to the component pool list, using the entity id as index.
        componentPool->Set(entityId, newComponent);

        // Change the signature of the entity to say that, entity has that component.
        EntityComponentSignatures[entityId].set(componentId);

        AddEntityToSystems(entity);

        return componentPool->Get(entityId);
    }

    template <typename TComponent>
    void Registry::RemoveComponent(const Entity entity)
    {
        const int componentId = Component<TComponent>::GetId();
        const int entityId = entity.GetId();

        EntityComponentSignatures[entityId].set(componentId);

        std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(ComponentPools[componentId]);
        componentPool->Remove(entityId);
    }

    template <typename TComponent>
    bool Registry::HasComponent(const Entity entity) const
    {
        const int componentId = Component<TComponent>::GetId();

        return EntityComponentSignatures[entity.GetId()].test(componentId);
    }

    template <typename TComponent>
    TComponent& Registry::GetComponent(const Entity entity) const
    {
        const int componentId = Component<TComponent>::GetId();
        const int entityId = entity.GetId();

        std::shared_ptr<Pool<TComponent>> componentPool = std::static_pointer_cast<Pool<TComponent>>(ComponentPools[componentId]);
        return componentPool->Get(entityId);
    }
#pragma endregion

#pragma region Registry System Template Functions

    template <typename TSystem, typename... TSystemArgs>
    void Registry::AddSystem(TSystemArgs&&... systemArgs)
    {
        const std::shared_ptr<TSystem> newSystem = std::make_shared<TSystem>(std::forward<TSystemArgs>(systemArgs)...);

        Systems.insert(std::make_pair(std::type_index(typeid(TSystem)), newSystem));
    }

    template <typename TSystem>
    void Registry::RemoveSystem()
    {
        Systems[typeid(TSystem)]->OnSystemRemoved();
        Systems.erase(std::type_index(typeid(TSystem)));
    }

    template <typename TSystem>
    bool Registry::HasSystem() const
    {
        return Systems.contains(std::type_index(typeid(TSystem)));
    }

    template <typename TSystem>
    TSystem& Registry::GetSystem() const
    {
        const auto systemPairKey = Systems.find(std::type_index(typeid(TSystem)));
        return *std::static_pointer_cast<TSystem>(systemPairKey->second);
    }
#pragma endregion

#pragma region Entity component functions
    template <typename TComponent, typename... TComponentArgs>
    TComponent& Entity::AddComponent(TComponentArgs&&... componentArgs)
    {
        return Registry->AddComponent<TComponent>(*this, std::forward<TComponentArgs>(componentArgs)...);
    }

    template <typename TComponent>
    void Entity::RemoveComponent() const
    {
        Registry->RemoveComponent<TComponent>(*this);
    }

    template <typename TComponent>
    bool Entity::HasComponent() const
    {
        return Registry->HasComponent<TComponent>(*this);
    }

    template <typename TComponent>
    bool Entity::TryGetComponent(TComponent& outComponent)
    {
        if (!Registry->HasComponent<TComponent>(*this))
        {
            return false;
        }

        outComponent = GetComponent<TComponent>();

        return true;
    }

    template <typename TComponent>
    TComponent& Entity::GetComponent() const
    {
        return Registry->GetComponent<TComponent>(*this);
    }
#pragma endregion
}
