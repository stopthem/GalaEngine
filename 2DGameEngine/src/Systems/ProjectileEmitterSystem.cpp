#include "ProjectileEmitterSystem.h"
#include <SDL_timer.h>
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/LifetimeComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/ProjectileComponent.h"
#include "../Logger/Logger.h"

ProjectileEmitterSystem::ProjectileEmitterSystem(Registry* registry)
    : RegistryPtr(registry)
{
    RequireComponent<TransformComponent>();
    RequireComponent<ProjectileEmitterComponent>();
}

void ProjectileEmitterSystem::Update()
{
    ForEachSystemEntity([&](Entity systemEntity)
    {
        const int currentTicks = static_cast<int>(SDL_GetTicks());

        ProjectileEmitterComponent& projectileEmitterComponent = systemEntity.GetComponent<ProjectileEmitterComponent>();

        if (currentTicks - projectileEmitterComponent.LastEmittedTime > projectileEmitterComponent.ProjectileEmittingInterval)
        {
            EmitProjectile(systemEntity, projectileEmitterComponent.EmitterProjectileParams);

            projectileEmitterComponent.LastEmittedTime = currentTicks;
        }
    });
}

void ProjectileEmitterSystem::EmitProjectile(Entity systemEntity, const ProjectileParams& projectileParams) const
{
    TransformComponent transformComponent;
    if (!systemEntity.TryGetComponent<TransformComponent>(transformComponent))
    {
        Logger::Log("entity with id " + std::to_string(systemEntity.GetId()) + " does not have a transform component to emit a projectile!");
        return;
    }

    glm::vec2 projectileLocation = transformComponent.Location;

    SpriteComponent foundSpriteComponent;
    // We check if we have a sprite component, we move projectile location left and upwards to center our entity because 0,0 is top left.
    if (!systemEntity.TryGetComponent<SpriteComponent>(foundSpriteComponent))
    {
        Logger::Log("entity with id " + std::to_string(systemEntity.GetId()) + " does not have a sprite component to emit a projectile!");
        return;
    }

    projectileLocation.x += transformComponent.Scale.x * static_cast<float>(foundSpriteComponent.Width) / 2;
    projectileLocation.y += transformComponent.Scale.y * static_cast<float>(foundSpriteComponent.Height) / 2;

    Entity projectile = RegistryPtr->CreateEntity();

    projectile.AddToGroup(GROUP_PROJECTILE);

    // Get angle of the bullet from atan2 of projectile vector.
    // Flip y because 0,0 is top left.
    projectile.AddComponent<TransformComponent>(projectileLocation,
                                                glm::vec2(1), std::atan2(projectileParams.ProjectileVector.x, -projectileParams.ProjectileVector.y));

    projectile.AddComponent<BoxColliderComponent>(4, 4);

    projectile.AddComponent<RigidbodyComponent>(projectileParams.ProjectileVector);

    projectile.AddComponent<ProjectileComponent>(projectileParams);

    projectile.AddComponent<LifetimeComponent>(projectileParams.LifetimeMiliSeconds);

    projectile.AddComponent<SpriteComponent>("bullet-texture", 4, 4, 4, false, true);
}
