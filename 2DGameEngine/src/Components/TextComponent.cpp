#include "TextComponent.h"

TextComponent::TextComponent(const glm::vec2& location, std::string text, std::string fontAssetId, const SDL_Color& color, const bool isFixed)
	:Location(location), Text(std::move(text)), FontAssetId(std::move(fontAssetId)), Color(color), IsFixed(isFixed)
{
}
