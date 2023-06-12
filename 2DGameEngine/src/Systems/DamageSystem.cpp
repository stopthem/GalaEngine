#include "DamageSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"

DamageSystem::DamageSystem(EventBus* eventBus)
{
	RequireComponent<BoxColliderComponent>();

	EventBusPtr = eventBus;
	EventBusPtr->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::OnCollision(CollisionEvent& collisionEvent)
{
}

void DamageSystem::OnSystemRemoved()
{
	System::OnSystemRemoved();

	EventBusPtr->UnSubscribeFromEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::Update()
{
}
