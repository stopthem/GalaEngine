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

void RenderSystem::Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect, const std::unique_ptr<AssetStore>& assetStore) const
{
	// Create a local struct so we don't have to get sprite and transform components again and again.
	struct RenderableEntity
	{
		TransformComponent transformComponent;
		SpriteComponent spriteComponent;
	};

	// Check all system entities for culling and add them to vector for rendering.
	std::vector<RenderableEntity> renderableEntities;
	for (Entity systemEntity : GetSystemEntities())
	{
		RenderableEntity renderableEntity;
		renderableEntity.spriteComponent = systemEntity.GetComponent<SpriteComponent>();
		renderableEntity.transformComponent = systemEntity.GetComponent<TransformComponent>();

		if (!renderableEntity.spriteComponent.IsFixed)
		{
			const glm::vec2 entityWithSpriteLocation = {
				renderableEntity.transformComponent.Location.x + renderableEntity.spriteComponent.Width * renderableEntity.transformComponent.Scale.x,
				renderableEntity.transformComponent.Location.y + renderableEntity.spriteComponent.Height * renderableEntity.transformComponent.Scale.y
			};
			if (entityWithSpriteLocation.x < cameraRect.x ||
				renderableEntity.transformComponent.Location.x > cameraRect.x + cameraRect.w ||
				renderableEntity.transformComponent.Location.y > cameraRect.y + cameraRect.h ||
				entityWithSpriteLocation.y < cameraRect.y)
			{
				continue;
			}
		}

		renderableEntities.emplace_back(renderableEntity);
	}

	// Sort by their spriteComponent.ZIndex ascending.
	std::sort(renderableEntities.begin(), renderableEntities.end(), [](const RenderableEntity& lhs, const RenderableEntity& rhs)
		{
			return lhs.spriteComponent.ZIndex < rhs.spriteComponent.ZIndex;
		});

	for (const auto& [transformComponent, spriteComponent] : renderableEntities)
	{
		SDL_Rect srcRect = spriteComponent.SrcRect;
		SDL_Rect dstRect{
			static_cast<int>(transformComponent.Location.x - (spriteComponent.IsFixed ? 0 : static_cast<float>(cameraRect.x))),
			static_cast<int>(transformComponent.Location.y - (spriteComponent.IsFixed ? 0 : static_cast<float>(cameraRect.y))),
			static_cast<int>(static_cast<float>(spriteComponent.Width) * transformComponent.Scale.x),
			static_cast<int>(static_cast<float>(spriteComponent.Height) * transformComponent.Scale.y),
		};

		SDL_RenderCopyEx(renderer, assetStore->GetTexture(spriteComponent.ImageAssetId), &srcRect, &dstRect
			, spriteComponent.Render0Angle ? 0 : transformComponent.Angle, nullptr, SDL_FLIP_NONE);
	}
}
