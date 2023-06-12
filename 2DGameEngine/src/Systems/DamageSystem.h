#pragma once

#include "../ECS/ECS.h"

class CollisionEvent;
class EventBus;
/*
 * DamageSystem
 *
 * System that handles damages based on collisions.
 */
class DamageSystem : public System
{
public:
	explicit DamageSystem(EventBus* eventBus);

public:
	void OnCollision(CollisionEvent& collisionEvent);

private:
	EventBus* EventBusPtr = nullptr;

public:
	// Unsubscribe from on collision event.
	void OnSystemRemoved() override;

public:
	void Update();
};