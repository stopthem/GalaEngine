#pragma once

#include "../ECS/ECS.h"

namespace gala
{
class CollisionEvent;
class EventBus;

    class MovementSystem : public System
    {
    public:
        explicit MovementSystem(EventBus* eventBus);
        ~MovementSystem() override;

    public:
        void Update(double deltaTime, const std::unique_ptr<Registry>& registry);

    private:
        void OnCollision(CollisionEvent& collisionEvent);

        void OnSystemRemoved() override;
    private:
        EventBus* EventBusPtr;

    };
}

