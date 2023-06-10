#include "BoxColliderComponent.h"
#include "TransformComponent.h"
#include "glm/glm.hpp"

BoxColliderComponent::BoxColliderComponent(const int width, const int height, const glm::vec2 offset)
	:Width(width), Height(height), Offset(offset)
{
}
