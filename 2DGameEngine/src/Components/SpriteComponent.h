#pragma once

#include <SDL_rect.h>
#include <string>
#include "glm/vec2.hpp"

/*
 * SpriteComponent
 *
 * Component used to render sprites.
 * Holds information about sprite width, height, z index, source rect and asset id.
 */
struct SpriteComponent
{
public:
    explicit SpriteComponent(std::string imageFilePath = "", int width = 32, int height = 32, int zIndex = 0
                             , bool isFixed = false, bool render0Angle = true, glm::vec2 srcPos = glm::vec2(0));

    SpriteComponent(const SpriteComponent& spriteComponent) = default;
public:
    // File path of the texture used by this sprite and loaded by AssetStore.
    std::string ImageFilePath;

    int Height;
    int Width;

    // If nullptr, uses full of the sprite.
    // Can be used to get a section of a sprite.
    SDL_Rect SrcRect;

    // Render order.
    // More is rendered on top.
    int ZIndex;

    // Should this sprite always remain in screen at a fixed location ?
    bool IsFixed;

    // Used by RenderSystem for always rendering this sprite at 0 angle.
    // This is useful when we rotate the entity but the animations need to have a 0 angle.
    bool Render0Angle;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(SpriteComponent, ImageFilePath, Width, Height, ZIndex, IsFixed, Render0Angle)
};
