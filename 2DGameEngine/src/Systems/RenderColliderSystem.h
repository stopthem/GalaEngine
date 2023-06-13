#pragma once

#include "../ECS/ECS.h"

struct SDL_Renderer;
struct SDL_Rect;
/*
 * RenderColliderSystem
 *
 * Renders all system entity's box collider bounds as a red rectangle when Game.IsDebug is true(toggled with "D" on keyboard).
 */
class RenderColliderSystem : public System
{
public:
	RenderColliderSystem();

public:

	void Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect) const;
};

