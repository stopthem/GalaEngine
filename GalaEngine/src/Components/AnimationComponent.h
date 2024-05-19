#pragma once

#include "nlohmann/json.hpp"

namespace gala
{
    /*
 * AnimationComponent
 *
 * Component used to animate sprites.
 */
    struct AnimationComponent
    {
    public:
        explicit AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool looping = true);

        AnimationComponent(const AnimationComponent& animationComponent) = default;

    public:
        int FrameSpeedRate = 1;

        bool Looping = true;

        int StartTime = 0;

        int CurrentFrame = 1;

        int NumFrames = 0;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(AnimationComponent, FrameSpeedRate, Looping)
    };
}
