#include "ProjectileEmitterSystem.h"
#include <SDL_timer.h>
#include "../Components/TransformComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/LifetimeComponent.h"
#include "../Components/SpriteComponent.h"

ProjectileEmitterSystem::ProjectileEmitterSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<ProjectileEmitterComponent>();
}

void ProjectileEmitterSystem::Update(const std::unique_ptr<Registry>& registry) const
{
	for (Entity systemEntity : GetSystemEntities())
	{
		const auto transformComponent = systemEntity.GetComponent<TransformComponent>();
		auto& projectileEmitterComponent = systemEntity.GetComponent<ProjectileEmitterComponent>();

		const int currentTicks = static_cast<int>(SDL_GetTicks());

		if (currentTicks - projectileEmitterComponent.LastEmittedTime > projectileEmitterComponent.ProjectileEmittingInterval)
		{
			glm::vec2 projectileLocation = transformComponent.Location;

			SpriteComponent foundSpriteComponent;
			if (systemEntity.TryGetComponent<SpriteComponent>(foundSpriteComponent))
			{
				projectileLocation.x += transformComponent.Scale.x * static_cast<float>(foundSpriteComponent.Width) / 2;
				projectileLocation.y += transformComponent.Scale.y * static_cast<float>(foundSpriteComponent.Height) / 2;
			}

			projectileEmitterComponent.LastEmittedTime = currentTicks;

			Entity projectile = registry->CreateEntity();

			projectile.AddComponent<TransformComponent>(projectileLocation,
				glm::vec2(1), std::atan2(projectileEmitterComponent.ProjectileVector.y, projectileEmitterComponent.ProjectileVector.x));

			projectile.AddComponent<BoxColliderComponent>(4, 4);

			projectile.AddComponent<RigidbodyComponent>(projectileEmitterComponent.ProjectileVector);

			projectile.AddComponent<LifetimeComponent>(projectileEmitterComponent.LifetimeMiliSeconds);

			projectile.AddComponent<SpriteComponent>("bullet-image", 4, 4, 4);
		}
	}
}
