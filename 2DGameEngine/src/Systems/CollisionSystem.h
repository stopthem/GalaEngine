#pragma once

#include "../ECS/ECS.h"

class EventBus;
struct BoxColliderComponent;
class CollisionSystem : public System
{
public:
	CollisionSystem();

public:
	void Update(const std::unique_ptr<EventBus>& eventBus) const;

private:
	// Checks box collision between 2 entities.
	[[nodiscard]] bool CheckAABBCollision(Entity sourceEntity, Entity targetEntity) const;

};

