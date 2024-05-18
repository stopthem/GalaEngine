#pragma once

#include "../ECS/ECS.h"

class AssetStore;
struct SDL_Renderer;
struct SDL_Rect;
/*
 * RenderHealthBarsSystem
 *
 *
 * System that handles rendering of health bars.
 */
class RenderHealthBarsSystem : public System
{
public:
	RenderHealthBarsSystem();

public:
	void Update(const std::unique_ptr<Registry>& registry, SDL_Renderer* renderer, const SDL_Rect& cameraRect);
};

