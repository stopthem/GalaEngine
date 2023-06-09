#include "RenderSystem.h"

#include <SDL_render.h>
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"
#include "../AssetStore/AssetStore.h"

RenderSystem::RenderSystem()
{
	RequireComponent<SpriteComponent>();
	RequireComponent<TransformComponent>();
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::Update(SDL_Renderer* renderer, const std::unique_ptr<AssetStore>& assetStore)
{
	for (Entity entity : GetSystemEntities())
	{
		auto spriteComponent = entity.GetComponent<SpriteComponent>();
		const auto transformComponent = entity.GetComponent<TransformComponent>();

		SDL_Rect srcRect = spriteComponent.SrcRect;
		SDL_Rect dstRect{
			static_cast<int>(transformComponent.Position.x),
			static_cast<int>(transformComponent.Position.y),
			static_cast<int>(static_cast<float>(spriteComponent.Width) * transformComponent.Scale.x),
			static_cast<int>(static_cast<float>(spriteComponent.Height) * transformComponent.Scale.y),
		};

		SDL_RenderCopyEx(renderer, assetStore->GetTexture(spriteComponent.ImageAssetId), &srcRect, &dstRect, transformComponent.Angle, nullptr, SDL_FLIP_NONE);
	}
}
