#include "LevelSerializer.h"

#include <fstream>

#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/HealthBarComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/LifetimeComponent.h"
#include "../Components/NameComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/ShootingComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/UUIDComponent.h"

namespace gala
{
    LevelSerializer::LevelSerializer(Registry* registry)
        : RegistryPtr(registry)
    {
    }

    static void SerializeEntity(Entity entity, nlohmann::json& json)
    {
        // First create a entry titled "Entity" so when we iterate through the "back" of this entry,
        // we know what those components belong to
        nlohmann::json entityJson{"Entity"};

        // Every entity has uuid component
        nlohmann::json uuidComponentJson = {typeid(UuidComponent).name(), entity.GetComponent<UuidComponent>()};
        // We serialize-deserialize uuid first because other components can reference this entity
        entityJson.push_back(uuidComponentJson);

        // Every entity has name component
        nlohmann::json nameComponentJson = {typeid(NameComponent).name(), entity.GetComponent<NameComponent>()};
        entityJson.push_back(nameComponentJson);

        // Check every component and if entity has that component, serialize and add it to the json

        if (AnimationComponent animationComponent; entity.TryGetComponent<AnimationComponent>(animationComponent))
        {
            nlohmann::json j = {typeid(AnimationComponent).name(), animationComponent};
            entityJson.push_back(j);
        }

        if (BoxColliderComponent boxColliderComponent; entity.TryGetComponent<BoxColliderComponent>(boxColliderComponent))
        {
            nlohmann::json j = {typeid(BoxColliderComponent).name(), boxColliderComponent};
            entityJson.push_back(j);
        }

        if (CameraFollowComponent cameraFollowComponent; entity.TryGetComponent<CameraFollowComponent>(cameraFollowComponent))
        {
            nlohmann::json j = {typeid(CameraFollowComponent).name(), cameraFollowComponent};
            entityJson.push_back(j);
        }

        if (HealthBarComponent healthBarComponent; entity.TryGetComponent<HealthBarComponent>(healthBarComponent))
        {
            nlohmann::json j = {typeid(HealthBarComponent).name(), healthBarComponent};
            entityJson.push_back(j);
        }

        if (HealthComponent healthComponent; entity.TryGetComponent<HealthComponent>(healthComponent))
        {
            nlohmann::json j = {typeid(HealthComponent).name(), healthComponent};
            entityJson.push_back(j);
        }

        if (KeyboardControlledComponent keyboardControlledComponent; entity.TryGetComponent<KeyboardControlledComponent>(keyboardControlledComponent))
        {
            nlohmann::json j = {typeid(KeyboardControlledComponent).name(), keyboardControlledComponent};
            entityJson.push_back(j);
        }

        if (LifetimeComponent lifetimeComponent; entity.TryGetComponent<LifetimeComponent>(lifetimeComponent))
        {
            nlohmann::json j = {typeid(LifetimeComponent).name(), lifetimeComponent};
            entityJson.push_back(j);
        }

        if (ProjectileComponent projectileComponent; entity.TryGetComponent<ProjectileComponent>(projectileComponent))
        {
            nlohmann::json j = {typeid(ProjectileComponent).name(), projectileComponent};
            entityJson.push_back(j);
        }

        if (ScriptComponent scriptComponent; entity.TryGetComponent<ScriptComponent>(scriptComponent))
        {
            nlohmann::json j = {typeid(ScriptComponent).name(), scriptComponent};
            entityJson.push_back(j);
        }

        if (ProjectileEmitterComponent projectileEmitterComponent; entity.TryGetComponent<ProjectileEmitterComponent>(projectileEmitterComponent))
        {
            nlohmann::json j = {typeid(ProjectileEmitterComponent).name(), projectileEmitterComponent};
            entityJson.push_back(j);
        }

        if (RigidbodyComponent rigidbodyComponent; entity.TryGetComponent<RigidbodyComponent>(rigidbodyComponent))
        {
            nlohmann::json j = {typeid(RigidbodyComponent).name(), rigidbodyComponent};
            entityJson.push_back(j);
        }

        if (ShootingComponent shootingComponent; entity.TryGetComponent<ShootingComponent>(shootingComponent))
        {
            nlohmann::json j = {typeid(ShootingComponent).name(), shootingComponent};
            entityJson.push_back(j);
        }

        if (SpriteComponent spriteComponent; entity.TryGetComponent<SpriteComponent>(spriteComponent))
        {
            nlohmann::json j = {typeid(SpriteComponent).name(), spriteComponent};
            entityJson.push_back(j);
        }

        if (TextComponent textComponent; entity.TryGetComponent<TextComponent>(textComponent))
        {
            nlohmann::json j = {typeid(TextComponent).name(), textComponent};
            entityJson.push_back(j);
        }

        if (TransformComponent transformComponent; entity.TryGetComponent<TransformComponent>(transformComponent))
        {
            nlohmann::json j = {typeid(TransformComponent).name(), transformComponent};
            entityJson.push_back(j);
        }

        json.push_back(entityJson);
    }

    static void DeserializeEntity(const nlohmann::json& json, Entity& entity)
    {
        // Iterate through the json. We will have component names as front() and the components themselves as back()
        for (auto& jsonElement : json)
        {
            if (jsonElement.front() == typeid(UuidComponent).name())
            {
                const UuidComponent deserializedUuidComponent = jsonElement.back();
                UuidComponent& uuidComponentOfEntity = entity.GetComponent<UuidComponent>();
                uuidComponentOfEntity = {deserializedUuidComponent};
            }

            if (jsonElement.front() == typeid(NameComponent).name())
            {
                const NameComponent deserializedNameComponent = jsonElement.back();
                NameComponent& nameComponentOfEntity = entity.GetComponent<NameComponent>();
                nameComponentOfEntity = {deserializedNameComponent};
            }

            if (jsonElement.front() == typeid(AnimationComponent).name())
            {
                const AnimationComponent animationComponent = jsonElement.back();
                entity.AddComponent<AnimationComponent>(animationComponent);
            }

            if (jsonElement.front() == typeid(BoxColliderComponent).name())
            {
                const BoxColliderComponent boxColliderComponent = jsonElement.back();
                entity.AddComponent<BoxColliderComponent>(boxColliderComponent);
            }

            if (jsonElement.front() == typeid(CameraFollowComponent).name())
            {
                const CameraFollowComponent cameraFollowComponent = jsonElement.back();
                entity.AddComponent<CameraFollowComponent>(cameraFollowComponent);
            }

            if (jsonElement.front() == typeid(HealthBarComponent).name())
            {
                const HealthBarComponent healthBarComponent = jsonElement.back();
                entity.AddComponent<HealthBarComponent>(healthBarComponent);
            }

            if (jsonElement.front() == typeid(HealthComponent).name())
            {
                const HealthComponent healthComponent = jsonElement.back();
                entity.AddComponent<HealthComponent>(healthComponent);
            }

            if (jsonElement.front() == typeid(KeyboardControlledComponent).name())
            {
                const KeyboardControlledComponent keyboardControlledComponent = jsonElement.back();
                entity.AddComponent<KeyboardControlledComponent>(keyboardControlledComponent);
            }

            if (jsonElement.front() == typeid(LifetimeComponent).name())
            {
                const LifetimeComponent lifetimeComponent = jsonElement.back();
                entity.AddComponent<LifetimeComponent>(lifetimeComponent);
            }

            if (jsonElement.front() == typeid(ProjectileComponent).name())
            {
                const ProjectileComponent projectileComponent = jsonElement.back();
                entity.AddComponent<ProjectileComponent>(projectileComponent);
            }

            if (jsonElement.front() == typeid(ProjectileEmitterComponent).name())
            {
                const ProjectileEmitterComponent projectileEmitterComponent = jsonElement.back();
                entity.AddComponent<ProjectileEmitterComponent>(projectileEmitterComponent);
            }

            if (jsonElement.front() == typeid(ProjectileEmitterComponent).name())
            {
                const ProjectileEmitterComponent projectileEmitterComponent = jsonElement.back();
                entity.AddComponent<ProjectileEmitterComponent>(projectileEmitterComponent);
            }

            if (jsonElement.front() == typeid(RigidbodyComponent).name())
            {
                const RigidbodyComponent rigidbodyComponent = jsonElement.back();
                entity.AddComponent<RigidbodyComponent>(rigidbodyComponent);
            }

            if (jsonElement.front() == typeid(ScriptComponent).name())
            {
                const ScriptComponent scriptComponent = jsonElement.back();
                entity.AddComponent<ScriptComponent>(scriptComponent);
            }

            if (jsonElement.front() == typeid(ShootingComponent).name())
            {
                const ShootingComponent shootingComponent = jsonElement.back();
                entity.AddComponent<ShootingComponent>(shootingComponent);
            }

            if (jsonElement.front() == typeid(SpriteComponent).name())
            {
                const SpriteComponent spriteComponent = jsonElement.back();
                entity.AddComponent<SpriteComponent>(spriteComponent);
            }

            if (jsonElement.front() == typeid(TextComponent).name())
            {
                const TextComponent textComponent = jsonElement.back();
                entity.AddComponent<TextComponent>(textComponent);
            }

            if (jsonElement.front() == typeid(TransformComponent).name())
            {
                const TransformComponent transformComponent = jsonElement.back();
                entity.AddComponent<TransformComponent>(transformComponent);
            }
        }
    }

    void LevelSerializer::SerializeLevel(const std::string& levelFilePath) const
    {
        nlohmann::json json;
        RegistryPtr->ForEachEntity([&](const Entity entity)
        {
            SerializeEntity(entity, json);
        });

        std::ofstream out(levelFilePath);
        out << json;
        out.close();
    }

    bool LevelSerializer::DeserializeLevel(const std::string& levelFilePath) const
    {
        std::ifstream loadedLevelFile(levelFilePath);

        if (loadedLevelFile.fail())
        {
            loadedLevelFile.close();
            return false;
        }

        nlohmann::json json = nlohmann::json::parse(loadedLevelFile);

        if (json.empty())
        {
            loadedLevelFile.close();
            return false;
        }

        for (auto& jsonElement : json.items())
        {
            if (jsonElement.value().front() == "Entity")
            {
                Entity createdEntity = RegistryPtr->CreateEntity();
                DeserializeEntity(jsonElement.value(), createdEntity);
            }
        }

        loadedLevelFile.close();
        return true;
    }
}
