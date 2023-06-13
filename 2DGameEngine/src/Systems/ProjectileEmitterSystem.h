#pragma once

#include "../ECS/ECS.h"

struct ProjectileParams;
/*
 * ProjectileEmitterSystem
 *
 * System that handles repetitive projectile emitting.
 */
class ProjectileEmitterSystem : public System
{
public:
	explicit ProjectileEmitterSystem(Registry* registry);

public:
	// Loop through all system entities and emit their projectiles if their timer is up.
	void Update() const;

	// This basically spawns a bullet towards entity's angle.
	// Its too strict i know.
	void EmitProjectile(Entity systemEntity, const ProjectileParams& projectileParams) const;

private:
	// Used to create a entity.
	Registry* RegistryPtr;
};

