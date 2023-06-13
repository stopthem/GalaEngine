#include "SpriteComponent.h"

SpriteComponent::SpriteComponent(std::string imageAssetId, const int width, const int height, const int zIndex, const bool isFixed, const glm::vec2 srcPos)
	: ImageAssetId(std::move(imageAssetId)), Height(height), Width(width)
	, SrcRect({ static_cast<int>(srcPos.x), static_cast<int>(srcPos.y), width, height })
	, ZIndex(zIndex), IsFixed(isFixed)
{
}