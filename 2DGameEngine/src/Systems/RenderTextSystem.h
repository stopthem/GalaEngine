#pragma once

#include "../ECS/ECS.h"

struct SDL_Renderer;
struct SDL_Rect;
class AssetStore;
/*
 * RenderTextSystem
 *
 * System that handles rendering of texts.
 */
class RenderTextSystem :public System
{
public:
	RenderTextSystem();

public:
	void Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect, const std::unique_ptr<AssetStore>& assetStore) const;
};

