#pragma once
#include "glm/vec2.hpp"

namespace gala
{
    /*
 * KeyboardControlledComponent
 *
 * Component used to move entity with arrow keys.
 * Sets entity's velocity based on keyboard arrow inputs.
 */
    struct KeyboardControlledComponent
    {
    public:
        explicit KeyboardControlledComponent(float speed = 1.0f);

        KeyboardControlledComponent(const KeyboardControlledComponent& keyboardControlledComponent) = default;

    public:
        float Speed;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(KeyboardControlledComponent, Speed)
    };
}
