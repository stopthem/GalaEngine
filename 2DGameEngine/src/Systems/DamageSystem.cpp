#include "DamageSystem.h"
#include "../Components/BoxColliderComponent.h"
#include "../EventBus/EventBus.h"
#include "../Logger/Logger.h"

DamageSystem::DamageSystem()
{
	RequireComponent<BoxColliderComponent>();
}

void DamageSystem::Setup(EventBus* eventBus)
{
	EventBusPtr = eventBus;
	EventBusPtr->SubscribeToEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::OnCollision(CollisionEvent& collisionEvent)
{
	Logger::Log("on collision happened!");
	EventBusPtr->UnSubscribeFromEvent<CollisionEvent>(this, &DamageSystem::OnCollision);
}

void DamageSystem::OnSystemRemoved()
{
}

void DamageSystem::Update()
{
}
