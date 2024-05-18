#include "RenderHealthBarsSystem.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include "../AssetStore/AssetStore.h"
#include "../Components/HealthBarComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/TextComponent.h"
#include "glm/gtx/compatibility.hpp"
#include "../Systems/RenderTextSystem.h"

RenderHealthBarsSystem::RenderHealthBarsSystem()
{
    RequireComponent<HealthComponent>();
    RequireComponent<HealthBarComponent>();
    RequireComponent<TransformComponent>();
}

void RenderHealthBarsSystem::Update(const std::unique_ptr<Registry>& registry, SDL_Renderer* renderer, const SDL_Rect& cameraRect)
{
    ForEachSystemEntity([&](Entity systemEntity)
    {
        const auto healthComponent = systemEntity.GetComponent<HealthComponent>();
        const auto transformComponent = systemEntity.GetComponent<TransformComponent>();

        // The rect will be not fixed, so we need to calculate where will it be when the camera moves.
        const int transformCameraX = static_cast<int>(transformComponent.Location.x - static_cast<float>(cameraRect.x));
        const int transformCameraY = static_cast<int>(transformComponent.Location.y - static_cast<float>(cameraRect.y));

        const auto healthNormalized = static_cast<float>(healthComponent.GetHealthNormalized());

        // First lerp from red to green with a being healthNormalized.
        const glm::vec3 lerpedColorVector = lerp(glm::vec3(255, 0, 0), glm::vec3(0, 255, 0), healthNormalized);
        // Create sdl color with lerpedColorVector.
        const SDLColorWrapper healthBarColor = {static_cast<Uint8>(lerpedColorVector.x), static_cast<Uint8>(lerpedColorVector.y), static_cast<Uint8>(lerpedColorVector.z), 255};

        // Create text component params for the text we will render top of the actual bar.
        TextComponentParams textComponentParams = TextComponentParams();
        textComponentParams.Text = std::to_string(static_cast<int>(healthNormalized * 100.0f)) + "%";
        textComponentParams.Location = {transformCameraX, transformCameraY - 10};
        textComponentParams.Color = healthBarColor;
        textComponentParams.IsFixed = false;
        textComponentParams.FontAssetId = "pico8-font-5";
        textComponentParams.FontSize = 16;

        // Render the percent text.
        registry->GetSystem<RenderTextSystem>().RenderText(textComponentParams);

        // Set our rect color.
        SDL_SetRenderDrawColor(renderer, healthBarColor.r, healthBarColor.g, healthBarColor.r, healthBarColor.a);

        // // Create a sdl rect under the text created by render text system.
        // // This is the actual bar.
        // SDL_Rect healthBarRect = {
        //     transformCameraX,
        //     (transformCameraY - 2),
        //     static_cast<int>(25 * healthNormalized),
        //     2
        // };
        //
        // SDL_RenderFillRect(renderer, &healthBarRect);
    });
}
