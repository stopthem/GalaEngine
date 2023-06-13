#pragma once

#include "../ECS/ECS.h"

class ProjectileEmitterSystem : public System
{
public:
	ProjectileEmitterSystem();

public:
	void Update(const std::unique_ptr<Registry>& registry) const;
};

