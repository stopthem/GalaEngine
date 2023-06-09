#include "Game.h"
#include <SDL.h>
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

void Game::AddSystems() const
{
	Registry->AddSystem<MovementSystem>();
	Registry->AddSystem<RenderSystem>();
}

void Game::AddAssets() const
{
	AssetStore->AddTexture(Renderer, "tank-image", "./assets/images/tank-panther-right.png");
	AssetStore->AddTexture(Renderer, "truck-image", "./assets/images/truck-ford-right.png");
}

void Game::Setup()
{
	AddSystems();

	AddAssets();

	Entity tank = Registry->CreateEntity();
	tank.AddComponent<RigidbodyComponent>(glm::vec2(10));
	tank.AddComponent<TransformComponent>(glm::vec2(1), glm::vec2(3), 45.0);
	tank.AddComponent<SpriteComponent>("tank-image", 32, 32);
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
