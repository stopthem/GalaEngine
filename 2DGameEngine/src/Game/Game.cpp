#include "Game.h"

#include <fstream>
#include <SDL.h>
#include <sstream>
#include "../Utility/StringUtilities.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Components/SpriteComponent.h"
#include "../AssetStore/AssetStore.h"

Game::Game()
	: Registry(std::make_unique<class Registry>()), AssetStore(std::make_unique<class AssetStore>())
{
}

Game::~Game()
= default;

void Game::Initialize()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		Logger::Err("Error initializing SDL.");
		return;
	}

	SDL_DisplayMode displayMode;
	SDL_GetCurrentDisplayMode(0, &displayMode);

	WindowWidth = displayMode.w;
	WindowHeight = displayMode.h;

	Window = SDL_CreateWindow(nullptr, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHeight, SDL_WINDOW_BORDERLESS);

	if (!Window)
	{
		Logger::Err("Error creating SDL window.");
		return;
	}

	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_PRESENTVSYNC);

	if (!Renderer)
	{
		Logger::Err("Error creating SDL renderer.");
		return;
	}

	SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);

	IsRunning = true;
}


void Game::Setup()
{
	LoadLevel(0);
}

void Game::LoadLevel(const int level) const
{
	AddSystems();

	AddAssets();

	CreateTileMap();

	Entity tank = Registry->CreateEntity();
	tank.AddComponent<RigidbodyComponent>(glm::vec2(10));
	tank.AddComponent<TransformComponent>(glm::vec2(1), glm::vec2(1), 45.0);
	tank.AddComponent<SpriteComponent>("tank-image", 32, 32);
}

void Game::AddSystems() const
{
	Registry->AddSystem<MovementSystem>();
	Registry->AddSystem<RenderSystem>();
}

void Game::CreateTileMap() const
{
	// First, lets read the .map file and get tile numbers for the pngs.
	std::vector<int> tileNumbers;

	std::ifstream readFile("./assets/tilemaps/jungle.map");

	std::string lineString;
	while (std::getline(readFile, lineString))
	{
		std::vector<std::string> splitLineNumberStrings = StringUtilities::Split(lineString, ",");
		for (const std::string& lineNumberString : splitLineNumberStrings)
		{
			tileNumbers.push_back(std::stoi(lineNumberString));
		}
	}

	constexpr double tileScale = 3.25;
	constexpr int tileSize = 32;
	// Then iterate through .map file columns and rows
	for (int y = 0; y < 20; ++y)
	{
		for (int x = 0; x < 25; ++x)
		{
			// Find 1d pos of a 2d value in the vector.
			const int tileNumber = tileNumbers[(y * 25) + x];

			// Find x tiling of the image which is 10x3.
			const int textureTilingX = (tileNumber % 10) * tileSize;
			// Find y tiling of the image which is 10x3.
			const int textureTilingY = (tileNumber / 10) * tileSize;

			Entity entity = Registry->CreateEntity();

			const glm::vec2 entityLocation(x * (tileSize * tileScale), y * (tileSize * tileScale));

			entity.AddComponent<TransformComponent>(entityLocation, glm::vec2(tileScale), 0.0);

			entity.AddComponent<SpriteComponent>("jungle-tilemap", tileSize, tileSize, glm::vec2(textureTilingX, textureTilingY));
		}
	}
}

void Game::AddAssets() const
{
	AssetStore->AddTexture(Renderer, "tank-image", "./assets/images/tank-panther-right.png");
	AssetStore->AddTexture(Renderer, "truck-image", "./assets/images/truck-ford-right.png");
	AssetStore->AddTexture(Renderer, "jungle-tilemap", "./assets/tilemaps/jungle.png");
}

void Game::Run()
{
	Setup();

	while (IsRunning)
	{
		ProcessInput();
		Update();
		Render();
	}
}

void Game::ProcessInput()
{
	SDL_Event sdlEvent;

	while (SDL_PollEvent(&sdlEvent))
	{
		switch (sdlEvent.type)
		{
		case SDL_QUIT:
			IsRunning = false;
			break;

		case SDL_KEYDOWN:
			if (sdlEvent.key.keysym.sym == SDLK_ESCAPE)
			{
				IsRunning = false;
			}
			break;
		}
	}
}

void Game::Update()
{
	const int currentFrameTicks = static_cast<int>(SDL_GetTicks());

	const int timeToWait = MILISECS_PER_FRAME - (currentFrameTicks - MilisecsPrevFrame);
	if (timeToWait > 0 && timeToWait <= MILISECS_PER_FRAME)
	{
		SDL_Delay(timeToWait);
	}

	DeltaTime = (currentFrameTicks - MilisecsPrevFrame) / 1000.0;

	// Store current frame as a previous frame for next frame.
	MilisecsPrevFrame = currentFrameTicks;

	// Ask all the systems to update.
	Registry->GetSystem<MovementSystem>().Update(DeltaTime);

	// Update the registry to process the entities that are waiting to be created/deleted.
	Registry->Update();
}

void Game::Render() const
{
	SDL_SetRenderDrawColor(Renderer, 21, 21, 21, 255);
	SDL_RenderClear(Renderer);

	// Ask all render systems that needs a update.
	Registry->GetSystem<RenderSystem>().Update(Renderer, AssetStore);

	SDL_RenderPresent(Renderer);
}

void Game::Destroy() const
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
