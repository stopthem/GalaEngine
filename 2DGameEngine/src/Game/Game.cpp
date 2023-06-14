#include "Game.h"

#include <fstream>
#include <SDL.h>
#include <sstream>
#include "../Utility/StringUtilities.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/ShootingComponent.h"
#include "../Components/TextComponent.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
#include "../Systems/MovementSystem.h"
#include "../Systems/RenderSystem.h"
#include "../Systems/AnimationSystem.h"
#include "../Systems/CollisionSystem.h"
#include "../Systems/DamageSystem.h"
#include "../Systems/KeyboardControlSystem.h"
#include "../Systems/CameraMovementSystem.h"
#include "../Systems/RenderColliderSystem.h"
#include "../Systems/ProjectileEmitterSystem.h"
#include "../Systems/LifetimeSystem.h"
#include "../Systems/ShootingSystem.h"
#include "../Systems/RenderTextSystem.h"
#include "../AssetStore/AssetStore.h"
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"

int Game::WindowWidth;
int Game::WindowHeight;

double Game::MapWidth;
double Game::MapHeight;

Game::Game()
	: Registry(std::make_unique<class Registry>()), AssetStore(std::make_unique<class AssetStore>()), EventBus(std::make_unique<class EventBus>())
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

	if (TTF_Init() != 0)
	{
		Logger::Err("Error initializing SDL TTF");
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

	//SDL_SetWindowFullscreen(Window, SDL_WINDOW_FULLSCREEN);

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
	tank.AddComponent<RigidbodyComponent>(glm::vec2(0, 0));
	tank.AddComponent<TransformComponent>(glm::vec2(300, 0), glm::vec2(2), 0);
	tank.AddComponent<SpriteComponent>("tank-image", 32, 32, 1, false, true);
	tank.AddComponent<BoxColliderComponent>(32, 32);
	tank.AddComponent<ProjectileEmitterComponent>(ProjectileParams(glm::vec2(50, 0), false, 5), 3000);
	tank.AddComponent<HealthComponent>(10);
	tank.AddToGroup(GROUP_ENEMY);

	Entity truck = Registry->CreateEntity();
	truck.AddComponent<RigidbodyComponent>(glm::vec2(0, 0));
	truck.AddComponent<TransformComponent>(glm::vec2(1), glm::vec2(2), 0);
	truck.AddComponent<SpriteComponent>("truck-image", 32, 32, 1, false, true);
	truck.AddComponent<BoxColliderComponent>(32, 32);
	truck.AddComponent<ProjectileEmitterComponent>(ProjectileParams(glm::vec2(0, 50), false, 5), 3000);
	truck.AddComponent<HealthComponent>(100);
	truck.AddToGroup(GROUP_ENEMY);

	// Player
	Entity chopper = Registry->CreateEntity();
	chopper.AddComponent<RigidbodyComponent>(glm::vec2(0));
	chopper.AddComponent<TransformComponent>(glm::vec2(WindowWidth / 2, 200), glm::vec2(2), 0);
	chopper.AddComponent<SpriteComponent>("chopper-image", 32, 32, 2, false, true);
	chopper.AddComponent<AnimationComponent>(2, 10);
	chopper.AddComponent<KeyboardControlledComponent>(150.0f);
	chopper.AddComponent<CameraFollowComponent>();
	chopper.AddComponent<HealthComponent>(10);
	chopper.AddComponent<ShootingComponent>(ProjectileParams(glm::vec2(0), true), 250);
	chopper.AddComponent<BoxColliderComponent>(32, 32);
	chopper.AddTag(TAG_PLAYER);
	chopper.AddToGroup(GROUP_FRIENDLY);

	Entity radar = Registry->CreateEntity();
	radar.AddComponent<RigidbodyComponent>(glm::vec2(0));
	radar.AddComponent<TransformComponent>(glm::vec2(WindowWidth - 164, 32), glm::vec2(2), 0.0);
	radar.AddComponent<SpriteComponent>("radar-image", 64, 64, 2, true);
	radar.AddComponent<AnimationComponent>(8, 7);

	Entity label = Registry->CreateEntity();
	SDL_Color labelColor = { 255,255,255 };
	label.AddComponent<TextComponent>(glm::vec2(WindowWidth / 2, 150), "Hello World!", "charriot-font", labelColor);
}

void Game::AddSystems() const
{
	Registry->AddSystem<MovementSystem>();
	Registry->AddSystem<RenderSystem>();
	Registry->AddSystem<RenderColliderSystem>();
	Registry->AddSystem<AnimationSystem>();
	Registry->AddSystem<CollisionSystem>();
	Registry->AddSystem<DamageSystem>(EventBus.get());
	Registry->AddSystem<KeyboardControlSystem>(EventBus.get());
	Registry->AddSystem<CameraMovementSystem>();
	Registry->AddSystem<LifetimeSystem>(Registry.get());
	Registry->AddSystem<ProjectileEmitterSystem>(Registry.get());
	Registry->AddSystem<ShootingSystem>(Registry.get(), EventBus.get());
	Registry->AddSystem<RenderTextSystem>();
}

void Game::AddAssets() const
{
	AssetStore->AddTexture(Renderer, "tank-image", "./assets/images/tank-panther-right.png");
	AssetStore->AddTexture(Renderer, "truck-image", "./assets/images/truck-ford-right.png");
	AssetStore->AddTexture(Renderer, "chopper-image", "./assets/images/chopper-spritesheet.png");
	AssetStore->AddTexture(Renderer, "bullet-image", "./assets/images/bullet.png");

	AssetStore->AddTexture(Renderer, "radar-image", "./assets/images/radar.png");

	AssetStore->AddTexture(Renderer, "jungle-tilemap", "./assets/tilemaps/jungle.png");

	AssetStore->AddFont("charriot-font", "./assets/fonts/charriot.ttf", 16);
}

void Game::CreateTileMap() const
{
	// First, lets read the .map file and get tile numbers for the tilemaps.
	std::vector<int> tileNumbers;

	// This automatically opens the file for us to read.
	std::ifstream readFile("./assets/tilemaps/jungle.map");

	std::string lineString;
	while (std::getline(readFile, lineString))
	{
		// Split line elements by ",".
		// This function is very useful and it gives us raw numbers without spaces.
		std::vector<std::string> splitLineNumberStrings = StringUtilities::Split(lineString, ",");

		// When we split a string, it gives us a vector of strings with numbers. Iterate through them to add to list.
		for (const std::string& lineNumberString : splitLineNumberStrings)
		{
			// Convert string to int and add to vector.
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

			// We have to leave space between for tileSize(32) * tileScale because image is 32x32.
			const glm::vec2 entityLocation(x * (tileSize * tileScale), y * (tileSize * tileScale));

			entity.AddComponent<TransformComponent>(entityLocation, glm::vec2(tileScale), 0.0);

			entity.AddComponent<SpriteComponent>("jungle-tilemap", tileSize, tileSize, 0, false, false, glm::vec2(textureTilingX, textureTilingY));

			entity.AddToGroup(GROUP_TILEMAP);
		}
	}

	MapWidth = (25 * tileSize) * tileScale;
	MapHeight = (20 * tileSize) * tileScale;
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
			const SDL_Keycode keycode = sdlEvent.key.keysym.sym;

			if (keycode == SDLK_ESCAPE)
			{
				IsRunning = false;
			}

			if (keycode == SDLK_d)
			{
				IsDebug = !IsDebug;
			}

			EventBus->BroadcastEvent<KeyPressedEvent>(keycode);
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
	Registry->GetSystem<ProjectileEmitterSystem>().Update();
	Registry->GetSystem<LifetimeSystem>().Update(DeltaTime);
	Registry->GetSystem<MovementSystem>().Update(DeltaTime);
	Registry->GetSystem<CollisionSystem>().Update(EventBus);
	Registry->GetSystem<AnimationSystem>().Update();
	Registry->GetSystem<CameraMovementSystem>().Update(CameraRect);

	// Update the registry to process the entities that are waiting to be created/deleted.
	Registry->Update();
}

void Game::Render() const
{
	SDL_SetRenderDrawColor(Renderer, 21, 21, 21, 255);
	SDL_RenderClear(Renderer);

	// Ask all render systems that needs a update.
	Registry->GetSystem<RenderSystem>().Update(Renderer, CameraRect, AssetStore);
	Registry->GetSystem<RenderTextSystem>().Update(Renderer, CameraRect, AssetStore);

	if (IsDebug)
	{
		Registry->GetSystem<RenderColliderSystem>().Update(Renderer, CameraRect);
	}

	SDL_RenderPresent(Renderer);
}

void Game::Destroy() const
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_Quit();
}
