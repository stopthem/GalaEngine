#pragma once

#include "../ECS/ECS.h"

struct SDL_Rect;

namespace gala
{
    /*
 * CameraMovementSystem
 *
 * System that handles camera movements including entity following. 
 */
    class CameraMovementSystem : public System
    {
    public:
        CameraMovementSystem();

    public:
        void Update(SDL_Rect& camera);
    };
}
