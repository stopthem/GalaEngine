#pragma once

#include "glm/vec2.hpp"

/*
 * RigidbodyComponent
 *
 * Component needed to move a object with its velocity.
 * Has no physics.
 */
struct RigidbodyComponent
{
public:
	explicit RigidbodyComponent(const glm::vec2& initialVelocity = glm::vec2(0));

public:
	glm::vec2 Velocity = glm::vec2(0);
};

