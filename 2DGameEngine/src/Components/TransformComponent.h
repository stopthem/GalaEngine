#pragma once

#include <glm/glm.hpp>

/*
 * TransformComponent
 *
 * Component need to have a entity presence in the scene.
 * Holds information about location, rotation and scale.
 */
struct TransformComponent
{
public:
	explicit TransformComponent(const glm::vec2& location = glm::vec2(1), const glm::vec2& scale = glm::vec2(1), const double rotation = 0.0);

public:
	glm::vec2 Location = glm::vec2(0);

	glm::vec2 Scale = glm::vec2(0);

	double Angle = 0.0;
};

