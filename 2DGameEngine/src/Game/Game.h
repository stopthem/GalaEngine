#pragma once
#include <memory>
#include <SDL_rect.h>

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

	void LoadLevel(int level) const;
	void AddAssets() const;
	void AddSystems() const;
	void CreateTileMap() const;

	void Run();
	void ProcessInput();
	void Update();
	void DebugRenderCollisionBoxes() const;

	void Render() const;

	void Destroy() const;

private:
	bool IsRunning = false;

	std::unique_ptr<Registry> Registry = nullptr;
	std::unique_ptr<AssetStore> AssetStore = nullptr;
	std::unique_ptr<EventBus> EventBus = nullptr;

private:
	SDL_Window* Window = nullptr;
	SDL_Renderer* Renderer = nullptr;
	SDL_Rect CameraRect;

public:
	static int WindowWidth;
	static int WindowHeight;

	static int MapWidth;
	static int MapHeight;

private:
	int MilisecsPrevFrame = 0;

	double DeltaTime = 0;

private:
	bool IsDebug = false;
};

