#pragma once
#include "glm/vec2.hpp"

/*
 * KeyboardControlledComponent
 *
 * Component used to move entity with arrow keys.
 * Sets entity's velocity based on keyboard arrow inputs.
 */
struct KeyboardControlledComponent
{
public:
	explicit KeyboardControlledComponent(float speed = 1.0f);

public:
	glm::vec2 UpVelocity;
	glm::vec2 RightVelocity;
	glm::vec2 DownVelocity;
	glm::vec2 LeftVelocity;
};

