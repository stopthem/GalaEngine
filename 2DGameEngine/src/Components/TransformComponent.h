#pragma once

#include <glm/glm.hpp>

struct TransformComponent
{
public:
	explicit TransformComponent(const glm::vec2& position = glm::vec2(1), const glm::vec2& scale = glm::vec2(1), const double rotation = 0.0);

public:
	glm::vec2 Position = glm::vec2(0);

	glm::vec2 Scale = glm::vec2(0);

	double Rotation = 0.0;
};

