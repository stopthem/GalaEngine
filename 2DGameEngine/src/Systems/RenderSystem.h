#pragma once

#include "../ECS/ECS.h"

class AssetStore;
struct SDL_Renderer;
class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem() override;

public:
	void Update(SDL_Renderer* renderer, const std::unique_ptr<AssetStore>& assetStore);
};

