#pragma once

#include <glm/glm.hpp>
#include "../ECS/ECS.h"

struct TransformComponent
{
	glm::vec2 position;

	glm::vec2 scale;

	double rotation;

	TransformComponent() = default;
};

