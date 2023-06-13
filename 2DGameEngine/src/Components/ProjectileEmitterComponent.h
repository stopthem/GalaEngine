#pragma once

#include <glm/vec2.hpp>

struct ProjectileEmitterComponent
{
public:
	explicit ProjectileEmitterComponent(glm::vec2 projectileVector = glm::vec2(0), int projectileEmittingInterval = 1000, bool isFriendly = false, double damageAmount = 10, int lifetimeMiliseconds = 5000);

public:
	glm::vec2 ProjectileVector;

	int ProjectileEmittingInterval;
	int LastEmittedTime;

	int LifetimeMiliSeconds;

	bool IsFriendly;

	double DamageAmount;
};