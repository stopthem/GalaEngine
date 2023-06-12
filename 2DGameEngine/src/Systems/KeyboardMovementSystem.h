#pragma once

#include <SDL_keycode.h>
#include "../ECS/ECS.h"

class EventBus;
class KeyPressedEvent;
/*
 * KeyboardMovementSystem
 *
 * Currently handles only key pressed events.
 */
class KeyboardMovementSystem : public System
{
public:
	explicit KeyboardMovementSystem(EventBus* eventBus);

private:
	EventBus* EventBusPtr;

private:
	void OnKeyboardKeyPressed(KeyPressedEvent& keyPressedEvent);

public:
	void OnSystemRemoved() override;

};

