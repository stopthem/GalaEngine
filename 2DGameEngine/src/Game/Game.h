#pragma once

class Registry;
struct SDL_Window;
struct SDL_Renderer;

constexpr int FPS = 60;
constexpr int MILISECS_PER_FRAME = 1000 / FPS;
/*
* Game
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
	void Render() const;

	void Destroy() const;

private:
	bool IsRunning = false;

	Registry* Registry;

private:
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;

private:
	int WindowWidth = 0;
	int WindowHeight = 0;

private:
	int MilisecsPrevFrame = 0;

	double DeltaTime = 0;
};

