#pragma once

#include "ProjectileComponent.h"

/*
 * ProjectileEmitterComponent
 *
 * Component that holds information about projectile params and projectile emitting interval.
 */
struct ProjectileEmitterComponent
{
public:
	explicit ProjectileEmitterComponent(const ProjectileParams& projectileParams = ProjectileParams(), int projectileEmittingInterval = 1000);

public:
	ProjectileParams EmitterProjectileParams;

	int ProjectileEmittingInterval;
	int LastEmittedTime;
};
