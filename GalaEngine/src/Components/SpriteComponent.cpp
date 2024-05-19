#include "SpriteComponent.h"

namespace gala
{
    SpriteComponent::SpriteComponent(std::string imageFilePath, const int width, const int height, const int zIndex, const bool isFixed, const bool render0Angle, const glm::vec2 srcPos)
        : ImageFilePath(std::move(imageFilePath)), Height(height), Width(width)
          , SrcRect({static_cast<int>(srcPos.x), static_cast<int>(srcPos.y), width, height})
          , ZIndex(zIndex), IsFixed(isFixed), Render0Angle(render0Angle)
    {
    }
}
