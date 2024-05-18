#pragma once

#include <SDL_pixels.h>
#include <string>

#include "../EngineTypes/SDLColorWrapper.h"
#include "glm/vec2.hpp"

struct TextComponentParams
{
public:
    explicit TextComponentParams(const glm::vec2& location = glm::vec2(0),
                                 std::string text = "", std::string fontAssetId = "pico8-font-10", int fontSize = 12, const SDLColorWrapper& color = SDLColorWrapper(), bool isFixed = true);

public:
    glm::vec2 Location;

    std::string Text;

    std::string FontAssetId;

    int FontSize;

    SDLColorWrapper Color;

    bool IsFixed;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextComponentParams, Text, FontAssetId, FontSize, IsFixed, Color)
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

public:
    TextComponentParams TextParams;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(TextComponent, TextParams)
};
