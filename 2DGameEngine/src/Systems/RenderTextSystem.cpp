#include "RenderTextSystem.h"
#include <SDL_surface.h>
#include <SDL_ttf.h>

#include "../AssetStore/AssetStore.h"
#include "../Components/TextComponent.h"

RenderTextSystem::RenderTextSystem()
{
	RequireComponent<TextComponent>();
}

void RenderTextSystem::Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect, const std::unique_ptr<AssetStore>& assetStore) const
{
	for (Entity systemEntity : GetSystemEntities())
	{
		const auto textComponent = systemEntity.GetComponent<TextComponent>();

		SDL_Surface* surface = TTF_RenderText_Blended(assetStore->GetFont(textComponent.FontAssetId), textComponent.Text.c_str(), textComponent.Color);

		SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);

		// We don't need surface anymore.
		SDL_FreeSurface(surface);

		int textWidth = 0;
		int textHeight = 0;

		// Calculate width and height of the text with query.
		SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);

		SDL_Rect dstRect = {
			static_cast<int>(textComponent.Location.x - (textComponent.IsFixed ? 0 : static_cast<float>(cameraRect.x))),
			static_cast<int>(textComponent.Location.y - (textComponent.IsFixed ? 0 : static_cast<float>(cameraRect.y))),
			textWidth,
			textHeight
		};

		SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
	}
}
