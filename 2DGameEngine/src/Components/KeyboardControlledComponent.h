#pragma once
#include "glm/vec2.hpp"

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

