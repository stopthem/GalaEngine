#include "TextComponent.h"

TextComponentParams::TextComponentParams(const glm::vec2& location, std::string text, std::string fontAssetId, const SDL_Color& color, const bool isFixed)
	:Location(location), Text(std::move(text)), FontAssetId(std::move(fontAssetId)), Color(color), IsFixed(isFixed)
{
}

TextComponent::TextComponent(TextComponentParams textComponentParams)
	:TextParams(std::move(textComponentParams))
{
}
