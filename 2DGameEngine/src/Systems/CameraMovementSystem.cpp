#include "CameraMovementSystem.h"
#include <algorithm>
#include <SDL_rect.h>
#include "../Components/CameraFollowComponent.h"
#include "../Components/TransformComponent.h"
#include "../Game/Game.h"

CameraMovementSystem::CameraMovementSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<CameraFollowComponent>();
}

void CameraMovementSystem::Update(SDL_Rect& camera) const
{
	for (Entity systemEntity : GetSystemEntities())
	{
		const auto transformComponent = systemEntity.GetComponent<TransformComponent>();

		const int wantedCamXPos = transformComponent.Location.x - static_cast<float>(Game::WindowWidth) / 2;
		const int wantedCamYPos = transformComponent.Location.y - static_cast<float>(Game::WindowHeight) / 2;

		camera.x = std::clamp(wantedCamXPos, 0, static_cast<int>(std::abs(Game::MapWidth - Game::WindowWidth)));
		camera.y = std::clamp(wantedCamYPos, 0, static_cast<int>(std::abs(Game::MapHeight - Game::WindowHeight)));
	}
}
