#pragma once

/*
 * LifetimeComponent
 *
 * Component that holds information about lifetime and current timer in miliseconds.
 */
struct LifetimeComponent
{
public:
	explicit LifetimeComponent(int lifetimeMiliSeconds = 5000);

public:
	int LifetimeMiliSeconds;

	int CurrentTimerMiliSeconds = 0;
};

