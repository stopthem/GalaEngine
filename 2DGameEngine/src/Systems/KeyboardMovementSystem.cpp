#include "KeyboardMovementSystem.h"
#include <SDL_keyboard.h>
#include "../EventBus/EventBus.h"
#include "../Events/KeyPressedEvent.h"
#include "../Logger/Logger.h"

KeyboardMovementSystem::KeyboardMovementSystem(EventBus* eventBus)
{
	EventBusPtr = eventBus;
	EventBusPtr->SubscribeToEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::OnKeyboardKeyPressed);
}

void KeyboardMovementSystem::OnKeyboardKeyPressed(KeyPressedEvent& keyPressedEvent)
{
	const std::string keyName = SDL_GetKeyName(keyPressedEvent.PressedKeyCode);
	Logger::Log(keyName + " pressed!");
}

void KeyboardMovementSystem::OnSystemRemoved()
{
	System::OnSystemRemoved();

	EventBusPtr->UnSubscribeFromEvent<KeyPressedEvent>(this, &KeyboardMovementSystem::OnKeyboardKeyPressed);
}
