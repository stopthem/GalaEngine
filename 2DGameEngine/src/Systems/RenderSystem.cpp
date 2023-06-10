#include "RenderSystem.h"

#include <algorithm>
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
	// Copy our system entities to new vector for sorting.
	std::vector sortedEntities(GetSystemEntities());
	// Sort by their spriteComponent.ZIndex ascending.
	std::sort(sortedEntities.begin(), sortedEntities.end(), [](Entity& lhs, Entity& rhs)
		{
			const auto spriteComponentLhs = lhs.GetComponent<SpriteComponent>();
			const auto spriteComponentRhs = rhs.GetComponent<SpriteComponent>();
			return spriteComponentLhs.ZIndex < spriteComponentRhs.ZIndex;
		});

	for (Entity entity : sortedEntities)
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
