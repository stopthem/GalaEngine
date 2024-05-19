#include "KeyUpEvent.h"

namespace gala
{
    KeyUpEvent::KeyUpEvent(const SDL_Keycode keycode)
        :PressedKeyCode(keycode)
    {
    }
}
