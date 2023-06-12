#pragma once

#include "../ECS/ECS.h"

class AssetStore;
struct SDL_Renderer;
struct SDL_Rect;
/*
 * RenderSystem
 *
 * Renders sprites.
 */
class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem() override;

public:
	void Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect, const std::unique_ptr<AssetStore>& assetStore) const;
};

