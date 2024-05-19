#pragma once

#include "../ECS/ECS.h" 

namespace gala
{
    /*
 * RenderGUISystem 
 *
 * Simple im gui user system that shows a simple enemy spawner window.
 */
    class RenderGUISystem : public System
    {
    public:
        RenderGUISystem() = default;

    public:
        void Update(const std::unique_ptr<Registry>& registry) const;
    };
}

