#include "KeyboardControlSystem.h"
#include <SDL_keyboard.h>
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Logger/Logger.h"
#include "../Components/KeyboardControlledComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/TransformComponent.h"

KeyboardControlSystem::KeyboardControlSystem(EventBus* eventBus)
{
	RequireComponent<KeyboardControlledComponent>();
	RequireComponent<SpriteComponent>();
	RequireComponent<RigidbodyComponent>();
	RequireComponent<TransformComponent>();

	EventBusPtr = eventBus;
	EventBusPtr->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyboardKeyPressed);
}

void KeyboardControlSystem::OnKeyboardKeyPressed(KeyPressedEvent& keyPressedEvent)
{
	for (Entity systemEntity : GetSystemEntities())
	{
		const auto keyboardControlComponent = systemEntity.GetComponent<KeyboardControlledComponent>();
		auto& spriteComponent = systemEntity.GetComponent<SpriteComponent>();
		auto& rigidbodyComponent = systemEntity.GetComponent<RigidbodyComponent>();
		auto& transformComponent = systemEntity.GetComponent<TransformComponent>();

		glm::vec2 movingDirection;

		int spriteSheetRow = 0;

		switch (keyPressedEvent.PressedKeyCode)
		{
		case SDLK_UP:
			movingDirection = { 0,-1 };
			break;

		case SDLK_RIGHT:
			movingDirection = { 1,0 };

			spriteSheetRow = 1;
			break;

		case SDLK_DOWN:
			movingDirection = { 0,1 };

			spriteSheetRow = 2;
			break;

		case SDLK_LEFT:
			movingDirection = { -1,0 };

			spriteSheetRow = 3;
			break;

		default:
			// If there was no arrow key input, just return.
			return;
		}

		rigidbodyComponent.Velocity = { movingDirection.x * keyboardControlComponent.Speed, movingDirection.y * keyboardControlComponent.Speed };

		spriteComponent.SrcRect.y = spriteComponent.Height * spriteSheetRow;

		transformComponent.Angle = glm::degrees(static_cast<double>(std::atan2(movingDirection.x, -movingDirection.y)));
		Logger::Log(std::to_string(transformComponent.Angle));
	}
}

void KeyboardControlSystem::OnSystemRemoved()
{
	System::OnSystemRemoved();

	EventBusPtr->UnSubscribeFromEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyboardKeyPressed);
}
