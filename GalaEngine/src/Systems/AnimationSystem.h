#pragma once

#include "../ECS/ECS.h"

namespace gala
{
    class AnimationSystem : public System
    {
    public:
        AnimationSystem();

    public:
        void Update();
    };
}

