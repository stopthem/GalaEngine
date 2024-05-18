#pragma once
#include <nlohmann/json.hpp>

#include "glm/vec2.hpp"

/*
 * BoxColliderComponent
 *
 * Component used to handle collision.
 */
struct BoxColliderComponent
{
public:
    explicit BoxColliderComponent(int width = 0, int height = 0, glm::vec2 offset = glm::vec2(0));

public:
    int Width;
    int Height;

    glm::vec2 Offset;

public:

    NLOHMANN_DEFINE_TYPE_INTRUSIVE(BoxColliderComponent, Width, Height, Offset)
};
