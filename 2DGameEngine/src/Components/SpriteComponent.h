#pragma once

#include <SDL_rect.h>
#include <string>
#include "glm/vec2.hpp"

struct SpriteComponent
{
public:
	explicit  SpriteComponent(std::string imageAssetId = "", int width = 32, int height = 32, glm::vec2 srcPos = glm::vec2(0));
	~SpriteComponent();

public:
	std::string ImageAssetId;
	int Height;
	int Width;
	SDL_Rect SrcRect;
};
