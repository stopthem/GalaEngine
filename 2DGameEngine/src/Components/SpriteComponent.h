#pragma once

struct SpriteComponent
{
public:
	explicit  SpriteComponent(int width = 20, int height = 20);
	~SpriteComponent();

public:
	int Height;
	int Width;
};