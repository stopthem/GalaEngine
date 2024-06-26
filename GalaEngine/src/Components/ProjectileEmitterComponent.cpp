#include "ProjectileEmitterComponent.h"
#include <SDL_timer.h>

namespace gala
{
    ProjectileEmitterComponent::ProjectileEmitterComponent(const ProjectileParams& projectileParams, const int projectileEmittingInterval)
        : EmitterProjectileParams(projectileParams), ProjectileEmittingInterval(projectileEmittingInterval)
    {
        LastEmittedTime = static_cast<int>(SDL_GetTicks());
    }
}
