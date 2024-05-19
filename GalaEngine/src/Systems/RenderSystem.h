#pragma once

#include "../ECS/ECS.h"


struct SDL_Renderer;
struct SDL_Rect;
namespace gala
{
    class AssetStore;

    /*
 * RenderSystem
 *
 * Renders sprites.
 */
    class RenderSystem : public System
    {
    public:
        RenderSystem();
        ~RenderSystem() override;

    public:
        void Update(SDL_Renderer* renderer, const SDL_Rect& cameraRect, const std::unique_ptr<AssetStore>& assetStore);
    };
}
