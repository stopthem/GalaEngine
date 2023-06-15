#pragma once

#include <SDL_rect.h>
#include "../ECS/ECS.h"

struct TextComponentParams;
struct SDL_Renderer;
class AssetStore;
/*
 * RenderTextSystem
 *
 * System that handles rendering of texts.
 */
class RenderTextSystem : public System
{
public:
	explicit RenderTextSystem(SDL_Renderer* renderer, AssetStore* assetStore, const SDL_Rect& cameraRect);

public:
	// Loop through all system entities and render their texts.
	void Update() const;

	// Render a text based on text component params.
	void RenderText(const TextComponentParams& textComponentParams) const;

private:
	// Used to actually render the texts.
	SDL_Renderer* RendererPtr;

	// Used to retrieve fonts.
	AssetStore* AssetStorePtr;

	// Used to calculate camera position based on fixed location or not.
	SDL_Rect CameraRect;
};

