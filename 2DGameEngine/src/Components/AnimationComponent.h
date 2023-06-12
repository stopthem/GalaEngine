#pragma once

/*
 * AnimationComponent
 *
 * Component used to animate sprites.
 */
struct AnimationComponent
{
public:
	explicit AnimationComponent(int numFrames = 1, int frameSpeedRate = 1, bool looping = true);

public:
	int FrameSpeedRate = 1;

	bool Looping = true;

	int StartTime = 0;

	int CurrentFrame = 1;

	int NumFrames = 0;
};