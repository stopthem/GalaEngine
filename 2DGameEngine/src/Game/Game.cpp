#include "Game.h"
#include <SDL.h>
#include <iostream>
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"

Game::Game()
	: Registry(std::make_unique<class Registry>())
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
	Entity tank = Registry->CreateEntity();

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
	const int currentFrameTicks = SDL_GetTicks();

	const int timeToWait = MILISECS_PER_FRAME - (currentFrameTicks - MilisecsPrevFrame);
	if (timeToWait > 0 && timeToWait <= MILISECS_PER_FRAME)
	{
		SDL_Delay(timeToWait);
	}

	DeltaTime = (currentFrameTicks - MilisecsPrevFrame) / 1000.0;

	MilisecsPrevFrame = currentFrameTicks;
}

void Game::Render() const
{
	SDL_SetRenderDrawColor(Renderer, 21, 21, 21, 255);
	SDL_RenderClear(Renderer);

	SDL_RenderPresent(Renderer);
}

void Game::Destroy() const
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
