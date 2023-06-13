#pragma once

#include "../ECS/ECS.h"

struct SDL_Renderer;
struct SDL_Rect;
class RenderColliderSystem : public System
{
public:
	RenderColliderSystem();

public:

	void Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect) const;
};

