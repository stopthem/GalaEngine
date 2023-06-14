#include "DamageSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Components/HealthComponent.h"
#include "../Components/ProjectileComponent.h"

DamageSystem::DamageSystem(EventBus* eventBus)
{
	RequireComponent<BoxColliderComponent>();

	EventBusPtr = eventBus;
	EventBusPtr->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::OnCollision(CollisionEvent& collisionEvent)
{
	auto CheckProjectileHitEnemyOrPlayer = [&](Entity sourceEntity, Entity targetEntity)
	{
		// If source entity is not projectile return.
		// We check both entities that collisionEvent provides us so target entity can be projectile too.
		if (!sourceEntity.InGroup(GROUP_PROJECTILE))
		{
			return false;
		}

		// If target has no health component, we have nothing to damage.
		if (!targetEntity.HasComponent<HealthComponent>())
		{
			return false;
		}

		auto& targetHealth = targetEntity.GetComponent<HealthComponent>();

		const bool targetIsFriendly = targetEntity.InGroup(GROUP_FRIENDLY);

		const decltype(auto) projectileComponent = sourceEntity.GetComponent<ProjectileComponent>();
		
		if (targetIsFriendly && projectileComponent.IsFriendly)
		{
			return false;
		}

		if (!targetIsFriendly && !projectileComponent.IsFriendly)
		{
			return false;
		}

		targetHealth.Health -= projectileComponent.DamageAmount;

		if (targetHealth.Health <= 0)
		{
			targetEntity.Kill();
		}

		sourceEntity.Kill();

		return true;
	};

	// Check both entities that collisionEvent sent us.

	if (!CheckProjectileHitEnemyOrPlayer(collisionEvent.SourceEntity, collisionEvent.TargetEntity))
	{
		CheckProjectileHitEnemyOrPlayer(collisionEvent.TargetEntity, collisionEvent.SourceEntity);
	}
}

void DamageSystem::OnSystemRemoved()
{
	System::OnSystemRemoved();

	EventBusPtr->UnSubscribeFromEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::Update()
{
}
