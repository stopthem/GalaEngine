#include "RenderColliderSystem.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include "../Components/TransformComponent.h"
#include "../Components/BoxColliderComponent.h"

namespace gala
{
    RenderColliderSystem::RenderColliderSystem()
    {
        RequireComponent<TransformComponent>();
        RequireComponent<BoxColliderComponent>();
    }

    void RenderColliderSystem::Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect)
    {
        // Set render color to red.
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);

        // Iterate through collision system entities.
        ForEachSystemEntity([&](Entity systemEntity)
        {
            const auto entityTransformComponent = systemEntity.GetComponent<TransformComponent>();
            const auto entityBoxColliderComponent = systemEntity.GetComponent<BoxColliderComponent>();

            // Create a sdl rect with our entity's transform and box collider components.
            // Include offset of the box collision and scale of the transform too.
            SDL_Rect boxCollisionRect;
            boxCollisionRect.x = static_cast<int>(entityTransformComponent.Location.x + entityBoxColliderComponent.Offset.x) - cameraRect.x;
            boxCollisionRect.y = static_cast<int>(entityTransformComponent.Location.y + entityBoxColliderComponent.Offset.y) - cameraRect.y;
            boxCollisionRect.w = entityBoxColliderComponent.Width * static_cast<int>(entityTransformComponent.Scale.x);
            boxCollisionRect.h = entityBoxColliderComponent.Height * static_cast<int>(entityTransformComponent.Scale.y);

            SDL_RenderDrawRect(renderer, &boxCollisionRect);
        });
    }
}
