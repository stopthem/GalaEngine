#include "ShootingSystem.h"
#include "ProjectileEmitterSystem.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyUpEvent.h"
#include "../Components/TransformComponent.h"
#include "../Components/ShootingComponent.h"
#include "../Components/ProjectileEmitterComponent.h"

namespace gala
{
    ShootingSystem::ShootingSystem(Registry* registry, EventBus* eventBus)
        : RegistryPtr(registry), EventBusPtr(eventBus)
    {
        RequireComponent<TransformComponent>();
        RequireComponent<ShootingComponent>();

        EventBusPtr->SubscribeToEvent<KeyUpEvent>(this, &ShootingSystem::OnKeyUp);
    }

    void ShootingSystem::OnKeyUp(KeyUpEvent& keyUpEvent)
    {
        if (keyUpEvent.PressedKeyCode != SDLK_SPACE)
        {
            return;
        }

        ForEachSystemEntity([&](Entity systemEntity)
        {
            auto& shootingComponent = systemEntity.GetComponent<ShootingComponent>();
            const auto transformComponent = systemEntity.GetComponent<TransformComponent>();

            const double angleAsRadians = glm::radians(transformComponent.Angle);
            const glm::vec2 angleToV2Normalized = glm::normalize(glm::vec2(glm::degrees(std::sin(angleAsRadians)), -glm::degrees(std::cos(angleAsRadians))));

            shootingComponent.ShootingProjectileParams.ProjectileVector =
                {angleToV2Normalized.x * shootingComponent.BulletSpeed, angleToV2Normalized.y * shootingComponent.BulletSpeed};

            RegistryPtr->GetSystem<ProjectileEmitterSystem>().EmitProjectile(systemEntity, shootingComponent.ShootingProjectileParams);
        });
    }

    void ShootingSystem::OnSystemRemoved()
    {
        System::OnSystemRemoved();

        EventBusPtr->UnSubscribeFromEvent<KeyUpEvent>(this, &ShootingSystem::OnKeyUp);
    }
}
