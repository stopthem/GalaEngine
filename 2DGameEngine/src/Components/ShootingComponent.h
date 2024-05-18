#pragma once
#include "../Components/ProjectileComponent.h"

/*
 * ShootingComponent
 *
 * Struct that holds information about projectile parameters which will be shot and bullet speed.
 */
struct ShootingComponent
{
public:
    explicit ShootingComponent(const ProjectileParams& projectileParams = ProjectileParams(), double bulletSpeed = 25.0);

public:
    double BulletSpeed = 25.0;

    ProjectileParams ShootingProjectileParams;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ShootingComponent, ShootingProjectileParams, BulletSpeed)
};
