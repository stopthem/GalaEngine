#pragma once

#include <SDL_pixels.h>
#include <string>
#include "glm/vec2.hpp"

/*
 * TextComponent
 *
 * Component that holds necessary information for rendering a text.
 */
struct TextComponent
{
public:
	explicit TextComponent(const glm::vec2& location = glm::vec2(0),
		std::string text = "", std::string fontAssetId = "", const SDL_Color& color = SDL_Color(), bool isFixed = true);

public:
	glm::vec2 Location;

	std::string Text;

	std::string FontAssetId;

	SDL_Color Color;

	bool IsFixed;
};

