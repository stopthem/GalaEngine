#pragma once

#include <SDL_pixels.h>
#include <string>

#include "../EngineTypes/SDLColorWrapper.h"
#include "glm/vec2.hpp"

namespace gala
{
    struct TextComponentParams
    {
    public:
        explicit TextComponentParams(const glm::vec2& location = glm::vec2(0),
                                     std::string text = "", std::string fontFilePath = "./assets/fonts/pico8.ttf", int fontSize = 12, const SDLColorWrapper& color = SDLColorWrapper(), bool isFixed = true);

    public:
        glm::vec2 Location;

        std::string Text;

        std::string FontFilePath;

        int FontSize;

        SDLColorWrapper Color;

        bool IsFixed;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextComponentParams, Text, FontFilePath, FontSize, IsFixed, Color)
    };

    /*
 * TextComponent
 *
 * Component that holds necessary information for rendering a text.
 */
    struct TextComponent
    {
    public:
        explicit TextComponent(TextComponentParams textComponentParams = TextComponentParams());

        TextComponent(const TextComponent& textComponent) = default;

    public:
        TextComponentParams TextParams;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextComponent, TextParams)
    };
}
