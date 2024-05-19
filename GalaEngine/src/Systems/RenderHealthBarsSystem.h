#pragma once

#include "../ECS/ECS.h"

struct SDL_Rect;
struct SDL_Renderer;

namespace gala
{
    class AssetStore;
    /*
 * RenderHealthBarsSystem
 *
 *
 * System that handles rendering of health bars.
 */
    class RenderHealthBarsSystem : public System
    {
    public:
        RenderHealthBarsSystem();

    public:
        void Update(const std::unique_ptr<Registry>& registry, ::SDL_Renderer* renderer, const SDL_Rect& cameraRect);
    };
}
