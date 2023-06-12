#include "KeyboardControlledComponent.h"

KeyboardControlledComponent::KeyboardControlledComponent(float speed)
	:UpVelocity({ 0, -speed }), RightVelocity({ speed, 0 }), DownVelocity({ 0, speed }), LeftVelocity({ -speed, 0 })
{
}
