#include "TextComponent.h"

namespace gala
{
    TextComponentParams::TextComponentParams(const glm::vec2& location, std::string text, std::string fontFilePath, const int fontSize, const SDLColorWrapper& color, const bool isFixed)
        : Location(location), Text(std::move(text)), FontFilePath(std::move(fontFilePath)), FontSize(fontSize), Color(color), IsFixed(isFixed)
    {
    }

    TextComponent::TextComponent(TextComponentParams textComponentParams)
        : TextParams(std::move(textComponentParams))
    {
    }
}
