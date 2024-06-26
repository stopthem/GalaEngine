#include "TransformComponent.h"

namespace gala
{
    TransformComponent::TransformComponent(const glm::vec2& location, const glm::vec2& scale, const double rotation)
        :Location(location), Scale(scale), Angle(rotation)
    {
    }
}
