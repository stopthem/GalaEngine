#pragma once

#include "../ECS/ECS.h"
#include "glm/vec2.hpp"

struct BoxColliderComponent;
class CollisionSystem : public System
{
public:
	CollisionSystem();

public:
	void Update();

private:
	// Checks box collision between 2 entities.
	void CheckAABBCollision(Entity sourceEntity, Entity targetEntity) const;

};

