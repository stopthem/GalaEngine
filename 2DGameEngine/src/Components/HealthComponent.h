#pragma once

/*
 * HealthComponent
 *
 * Component that holds information about health.
 */
struct HealthComponent
{
public:
	explicit HealthComponent(int health = 100);

public:
	int Health;
};

