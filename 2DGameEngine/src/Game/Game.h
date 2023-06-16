#pragma once
#include <memory>
#include <SDL_rect.h>
#include <sol/sol.hpp>

class EventBus;
class Registry;
struct SDL_Window;
struct SDL_Renderer;
class AssetStore;

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
	void AddSystems() const;

	void Run();
	void ProcessInput();
	void Update();
	void Render() const;

	void Destroy() const;

private:
	bool IsRunning = false;

	std::unique_ptr<Registry> Registry = nullptr;
	std::unique_ptr<AssetStore> AssetStore = nullptr;
	std::unique_ptr<EventBus> EventBus = nullptr;

	sol::state Lua;

private:
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Rect CameraRect;

public:
	static int WindowWidth;
	static int WindowHeight;

	static double MapWidth;
	static double MapHeight;

private:
	int MilisecsPrevFrame = 0;

	double DeltaTime = 0;

private:
	bool IsDebug = false;
};

