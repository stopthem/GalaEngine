#include "AnimationComponent.h"
#include <SDL_timer.h>

AnimationComponent::AnimationComponent(const int numFrames, const int frameSpeedRate, const bool looping)
	: FrameSpeedRate(frameSpeedRate), Looping(looping), NumFrames(numFrames)
{
	StartTime = SDL_GetTicks();
}
