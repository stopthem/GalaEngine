#pragma once

struct SDL_Window;
struct SDL_Renderer;

constexpr int FPS = 60;
constexpr int MILLISECS_PER_FRAME = 1000 / FPS;
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

private:
	int windowWidth;
	int windowHeight;

private:
	int milisecsPrevFrame;

	double deltaTime;
};

