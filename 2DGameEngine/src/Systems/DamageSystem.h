#pragma once

#include "../ECS/ECS.h"

class CollisionEvent;
class EventBus;
class DamageSystem : public System
{
public:
	DamageSystem();

public:
	void Setup(EventBus* eventBus);

	void OnCollision(CollisionEvent& collisionEvent);

private:
	EventBus* EventBusPtr = nullptr;

public:
	void OnSystemRemoved() override;

public:
	void Update();
};