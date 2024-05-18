#include "AnimationSystem.h"

#include <SDL_timer.h>

#include "../Components/AnimationComponent.h"
#include "../Components/SpriteComponent.h"

AnimationSystem::AnimationSystem()
{
    RequireComponent<AnimationComponent>();
    RequireComponent<SpriteComponent>();
}

void AnimationSystem::Update()
{
    ForEachSystemEntity([](Entity systemEntity)
    {
        auto& animationComponent = systemEntity.GetComponent<AnimationComponent>();
        auto& spriteComponent = systemEntity.GetComponent<SpriteComponent>();

        animationComponent.CurrentFrame = ((static_cast<int>(SDL_GetTicks()) - animationComponent.StartTime)
            * animationComponent.FrameSpeedRate / 1000) % animationComponent.NumFrames;

        spriteComponent.SrcRect.x = animationComponent.CurrentFrame * spriteComponent.Width;
    });
}
