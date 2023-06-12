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

		glm::vec2 finalVelocity = rigidbodyComponent.Velocity;

		int spriteSheetRow = 0;

		switch (keyPressedEvent.PressedKeyCode)
		{
		case SDLK_UP:
			finalVelocity = keyboardControlComponent.UpVelocity;
			break;

		case SDLK_RIGHT:
			finalVelocity = keyboardControlComponent.RightVelocity;

			spriteSheetRow = 1;
			break;

		case SDLK_DOWN:
			finalVelocity = keyboardControlComponent.DownVelocity;

			spriteSheetRow = 2;
			break;

		case SDLK_LEFT:
			finalVelocity = keyboardControlComponent.LeftVelocity;

			spriteSheetRow = 3;
			break;

		default:
			// If there was no arrow key input, just return.
			return;
		}

		rigidbodyComponent.Velocity = finalVelocity;

		spriteComponent.SrcRect.y = spriteComponent.Height * spriteSheetRow;
	}
}

void KeyboardControlSystem::OnSystemRemoved()
{
	System::OnSystemRemoved();

	EventBusPtr->UnSubscribeFromEvent<KeyPressedEvent>(this, &KeyboardControlSystem::OnKeyboardKeyPressed);
}
