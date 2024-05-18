#include "RenderTextSystem.h"
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include "../AssetStore/AssetStore.h"
#include "../Components/TextComponent.h"

RenderTextSystem::RenderTextSystem(SDL_Renderer* renderer, AssetStore* assetStore, const SDL_Rect& cameraRect)
    : RendererPtr(renderer), AssetStorePtr(assetStore), CameraRect(cameraRect)
{
    RequireComponent<TextComponent>();
}

void RenderTextSystem::Update()
{
    ForEachSystemEntity([&](Entity systemEntity)
    {
        const auto textComponent = systemEntity.GetComponent<TextComponent>();

        RenderText(textComponent.TextParams);
    });
}

void RenderTextSystem::RenderText(const TextComponentParams& textComponentParams) const
{
    // SDL_Surface* surface = TTF_RenderText_Blended(AssetStorePtr->GetFont(textComponentParams.FontAssetId, textComponentParams.FontSize), textComponentParams.Text.c_str(), textComponentParams.Color.AsSDLColor());
    //
    // SDL_Texture* texture = SDL_CreateTextureFromSurface(RendererPtr, surface);
    //
    // // We don't need surface anymore.
    // SDL_FreeSurface(surface);
    //
    // int textWidth = 0;
    // int textHeight = 0;
    //
    // // Calculate width and height of the text with query.
    // SDL_QueryTexture(texture, nullptr, nullptr, &textWidth, &textHeight);
    //
    // const SDL_Rect dstRect = {
    //     static_cast<int>(textComponentParams.Location.x - (textComponentParams.IsFixed ? 0 : static_cast<float>(CameraRect.x))),
    //     static_cast<int>(textComponentParams.Location.y - (textComponentParams.IsFixed ? 0 : static_cast<float>(CameraRect.y))),
    //     textWidth,
    //     textHeight
    // };
    //
    // SDL_RenderCopy(RendererPtr, texture, nullptr, &dstRect);
    //
    // // We have no use for texture anymore.
    // SDL_DestroyTexture(texture);
}
