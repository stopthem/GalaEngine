#include "RenderSystem.h"

#include <SDL_rect.h>
#include <SDL_render.h>
#include "../Components/SpriteComponent.h"
#include "../Components/TransformComponent.h"

RenderSystem::RenderSystem()
{
	RequireComponent<SpriteComponent>();
	RequireComponent<TransformComponent>();
}

RenderSystem::~RenderSystem() = default;

void RenderSystem::Update(SDL_Renderer* renderer)
{
	for (Entity entity : GetSystemEntities())
	{
		const auto spriteComponent = entity.GetComponent<SpriteComponent>();
		const auto transformComponent = entity.GetComponent<TransformComponent>();

		SDL_Rect rect = {
			static_cast<int>(transformComponent.Position.x),
			static_cast<int>(transformComponent.Position.y),
			spriteComponent.Width,
			spriteComponent.Height };

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderFillRect(renderer, &rect);
	}
}
