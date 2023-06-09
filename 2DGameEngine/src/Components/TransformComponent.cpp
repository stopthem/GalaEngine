#include "TransformComponent.h"

TransformComponent::TransformComponent(const glm::vec2& position, const glm::vec2& scale, const double rotation)
	:Position(position), Scale(scale), Rotation(rotation)
{
}
