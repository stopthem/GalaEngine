#pragma once

#include "../ECS/ECS.h"

struct SDL_Renderer;
class RenderSystem : public System
{
public:
	RenderSystem();
	~RenderSystem() override;

public:
	void Update(SDL_Renderer* renderer);
};

