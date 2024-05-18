#include "LevelSerializer.h"

#include <fstream>

#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/HealthBarComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/LifetimeComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/ScriptComponent.h"
#include "../Components/ShootingComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/TextComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/UUIDComponent.h"
#include "../Logger/Logger.h"

LevelSerializer::LevelSerializer(Registry* registry)
    : RegistryPtr(registry)
{
}

static void SerializeEntity(Entity entity, nlohmann::json& json)
{
    nlohmann::json entityJson{"Entity"};
    // Every entity has uuid component
    nlohmann::json uuidComponentJson = {"UuidComponent", entity.GetComponent<UuidComponent>()};
    entityJson.push_back(uuidComponentJson);

    if (AnimationComponent animationComponent; entity.TryGetComponent<AnimationComponent>(animationComponent))
    {
        nlohmann::json j = {"AnimationComponent", animationComponent};
        entityJson.push_back(j);
    }

    if (BoxColliderComponent boxColliderComponent; entity.TryGetComponent<BoxColliderComponent>(boxColliderComponent))
    {
        nlohmann::json j = {"BoxColliderComponent", boxColliderComponent};
        entityJson.push_back(j);
    }

    if (CameraFollowComponent cameraFollowComponent; entity.TryGetComponent<CameraFollowComponent>(cameraFollowComponent))
    {
        nlohmann::json j = {"CameraFollowComponent", cameraFollowComponent};
        entityJson.push_back(j);
    }

    if (HealthBarComponent healthBarComponent; entity.TryGetComponent<HealthBarComponent>(healthBarComponent))
    {
        nlohmann::json j = {"HealthBarComponent", healthBarComponent};
        entityJson.push_back(j);
    }

    if (HealthComponent healthComponent; entity.TryGetComponent<HealthComponent>(healthComponent))
    {
        nlohmann::json j = {"HealthComponent", healthComponent};
        entityJson.push_back(j);
    }

    if (KeyboardControlledComponent keyboardControlledComponent; entity.TryGetComponent<KeyboardControlledComponent>(keyboardControlledComponent))
    {
        nlohmann::json j = {"KeyboardControlledComponent", keyboardControlledComponent};
        entityJson.push_back(j);
    }

    if (LifetimeComponent lifetimeComponent; entity.TryGetComponent<LifetimeComponent>(lifetimeComponent))
    {
        nlohmann::json j = {"LifetimeComponent", lifetimeComponent};
        entityJson.push_back(j);
    }

    if (ProjectileComponent projectileComponent; entity.TryGetComponent<ProjectileComponent>(projectileComponent))
    {
        nlohmann::json j = {"ProjectileComponent", projectileComponent};
        entityJson.push_back(j);
    }

    if (ScriptComponent scriptComponent; entity.TryGetComponent<ScriptComponent>(scriptComponent))
    {
        nlohmann::json j = {"ScriptComponent", scriptComponent};
        entityJson.push_back(j);
    }

    if (ProjectileEmitterComponent projectileEmitterComponent; entity.TryGetComponent<ProjectileEmitterComponent>(projectileEmitterComponent))
    {
        nlohmann::json j = {"ProjectileEmitterComponent", projectileEmitterComponent};
        entityJson.push_back(j);
    }

    if (RigidbodyComponent rigidbodyComponent; entity.TryGetComponent<RigidbodyComponent>(rigidbodyComponent))
    {
        nlohmann::json j = {"RigidbodyComponent", rigidbodyComponent};
        entityJson.push_back(j);
    }

    if (ShootingComponent shootingComponent; entity.TryGetComponent<ShootingComponent>(shootingComponent))
    {
        nlohmann::json j = {"ShootingComponent", shootingComponent};
        entityJson.push_back(j);
    }

    if (SpriteComponent spriteComponent; entity.TryGetComponent<SpriteComponent>(spriteComponent))
    {
        nlohmann::json j = {"SpriteComponent", spriteComponent};
        entityJson.push_back(j);
    }

    if (TextComponent textComponent; entity.TryGetComponent<TextComponent>(textComponent))
    {
        nlohmann::json j = {"TextComponent", textComponent};
        entityJson.push_back(j);
    }

    if (TransformComponent transformComponent; entity.TryGetComponent<TransformComponent>(transformComponent))
    {
        nlohmann::json j = {"TransformComponent", transformComponent};
        entityJson.push_back(j);
    }

    json.push_back(entityJson);
}

static void DeserializeEntity(const nlohmann::json& json, Entity& entity)
{
    for (auto& jsonElement : json)
    {
        if (jsonElement.front() == "UuidComponent")
        {
            const UuidComponent deserializedUuidComponent = jsonElement.back();
            UuidComponent& uuidComponentOfEntity = entity.GetComponent<UuidComponent>();
            uuidComponentOfEntity = {deserializedUuidComponent};
        }

        if (jsonElement.front() == "AnimationComponent")
        {
            const AnimationComponent animationComponent = jsonElement.back();
            entity.AddComponent<AnimationComponent>(animationComponent);
        }

        if (jsonElement.front() == "ProjectileEmitterComponent")
        {
            const ProjectileEmitterComponent projectileEmitterComponent = jsonElement.back();
            entity.AddComponent<ProjectileEmitterComponent>(projectileEmitterComponent);
        }

        if (jsonElement.front() == "TransformComponent")
        {
            const TransformComponent transformComponent = jsonElement.back();
            entity.AddComponent<TransformComponent>(transformComponent);
        }

        if (jsonElement.front() == "SpriteComponent")
        {
            const SpriteComponent spriteComponent = jsonElement.back();
            entity.AddComponent<SpriteComponent>(spriteComponent);
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
