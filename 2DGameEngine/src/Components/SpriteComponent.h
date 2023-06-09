#pragma once

#include <SDL_rect.h>
#include <string>
#include "glm/vec2.hpp"

struct SpriteComponent
{
public:
	explicit  SpriteComponent(std::string imageAssetId = "", int width = 20, int height = 20, glm::vec2 srcPos = glm::vec2(0));
	~SpriteComponent();

public:
	std::string ImageAssetId;
	int Height;
	int Width;

	SDL_Rect& GetSrcRect() { return SrcRect; }
private:
	SDL_Rect SrcRect;
};
