#include "ShootingComponent.h"

namespace gala
{
    ShootingComponent::ShootingComponent(const ProjectileParams& projectileParams, const double bulletSpeed)
        :BulletSpeed(bulletSpeed), ShootingProjectileParams(projectileParams)
    {
    }
}
