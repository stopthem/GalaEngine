#pragma once

#include "ProjectileComponent.h"

namespace gala
{
    /*
 * ProjectileEmitterComponent
 *
 * Component that holds information about projectile params and projectile emitting interval.
 */
    struct ProjectileEmitterComponent
    {
    public:
        explicit ProjectileEmitterComponent(const ProjectileParams& projectileParams = ProjectileParams(), int projectileEmittingInterval = 1000);

        ProjectileEmitterComponent(const ProjectileEmitterComponent& projectileEmitterComponent) = default;
    public:
        ProjectileParams EmitterProjectileParams;

        int ProjectileEmittingInterval;
        int LastEmittedTime;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ProjectileEmitterComponent, EmitterProjectileParams, ProjectileEmittingInterval)
    };
}
