#pragma once

#include "../ECS/ECS.h"

class MovementSystem : public System
{
public:
	MovementSystem();
	~MovementSystem() override;

public:
	void Update(double deltaTime) override;

};

