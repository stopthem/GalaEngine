#pragma once

#include <SDL_keycode.h>
#include "../EventBus/Event.h"

/*
 * KeyPressedEvent
 *
 * Key pressed event contains this class when its broadcasted.
 */
class KeyUpEvent : public Event
{
public:
	explicit KeyUpEvent(SDL_Keycode keycode);

public:
	SDL_Keycode PressedKeyCode;
};

