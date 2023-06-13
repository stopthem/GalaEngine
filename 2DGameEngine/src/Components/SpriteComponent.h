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
	explicit SpriteComponent(std::string imageAssetId = "", int width = 32, int height = 32, int zIndex = 0, bool isFixed = false, bool render0Angle = true, glm::vec2 srcPos = glm::vec2(0));

public:
	std::string ImageAssetId;

	int Height;
	int Width;

	SDL_Rect SrcRect;

	int ZIndex;

	bool IsFixed;

	bool Render0Angle;
};
