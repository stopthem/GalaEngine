#include "ShootingComponent.h"

ShootingComponent::ShootingComponent(const ProjectileParams& projectileParams, const double bulletSpeed)
	:BulletSpeed(bulletSpeed), ShootingProjectileParams(projectileParams)
{
}
