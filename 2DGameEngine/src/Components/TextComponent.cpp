#include "TextComponent.h"

TextComponentParams::TextComponentParams(const glm::vec2& location, std::string text, std::string fontAssetId, const int fontSize, const SDLColorWrapper& color, const bool isFixed)
    : Location(location), Text(std::move(text)), FontAssetId(std::move(fontAssetId)), FontSize(fontSize), Color(color), IsFixed(isFixed)
{
}

TextComponent::TextComponent(TextComponentParams textComponentParams)
    : TextParams(std::move(textComponentParams))
{
}
