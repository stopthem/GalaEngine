#pragma once
#include <SDL_pixels.h>
#include <nlohmann/json.hpp>

/*
 * SDLColorWrapper
 *
 * Struct that engine uses to wrap SDL_Color, so it can be serialized
 */
struct SDLColorWrapper
{
public:
    SDLColorWrapper() = default;

    explicit SDLColorWrapper(const SDL_Color& sdlColor)
    {
        r = sdlColor.r;
        g = sdlColor.g;
        b = sdlColor.b;
        a = sdlColor.a;
    }

    SDLColorWrapper(const Uint8 inR, const Uint8 inG, const Uint8 inB, const Uint8 inA)
    {
        r = inR;
        g = inG;
        b = inB;
        a = inA;
    }

    Uint8 r = 0, g = 0, b = 0, a = 0;

public:
    [[nodiscard]] SDL_Color AsSDLColor() const { return {r, g, b, a}; }

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SDLColorWrapper, r, g, b, a)
};
