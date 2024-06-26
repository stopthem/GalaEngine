#include "AnimationComponent.h"
#include <SDL_timer.h>

namespace gala
{
    AnimationComponent::AnimationComponent(const int numFrames, const int frameSpeedRate, const bool looping)
        : FrameSpeedRate(frameSpeedRate), Looping(looping), NumFrames(numFrames)
    {
        StartTime = static_cast<int>(SDL_GetTicks());
    }
}
