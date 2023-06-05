#pragma once

struct SDL_Window;
struct SDL_Renderer;
/*
* Game
*
*/
class Game
{
public:
	Game();
	~Game();

public:
	void Initialize();
	void Setup();

	void Run();
	void ProcessInput();
	void Update();
	void Render();

	void Destroy();

private:
	bool isRunning = false;

private:
	SDL_Window* window = nullptr;
	SDL_Renderer* renderer = nullptr;

public:
	int windowWidth;
	int windowHeight;
};

