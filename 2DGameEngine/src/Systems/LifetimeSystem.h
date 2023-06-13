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
	Registry* RegistryPtr;

public:
	void Update(double deltaTime) const;
};

