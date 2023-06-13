#pragma once

#include "../ECS/ECS.h"

/*
 * LifetimeSystem
 *
 * System that responsible for lifetime of the entities.
 */
class LifetimeSystem : public System
{
public:
	explicit LifetimeSystem(Registry* registry);

private:
	// Used to kill a entity.
	Registry* RegistryPtr;

public:
	// Loop through all system entities to check if their lifetime is up and kill them.
	void Update(double deltaTime) const;
};

