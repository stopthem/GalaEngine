#pragma once

#include "../ECS/ECS.h"

namespace gala
{
    class KeyUpEvent;
    class ProjectileEmitterSystem;
    class EventBus;

    /*
     * ShootingSystem
     *
     * System that shoots a projectile on key up
     */
    class ShootingSystem : public System
    {
    public:
        explicit ShootingSystem(Registry* registry, EventBus* eventBus);

    public:
        void OnKeyUp(KeyUpEvent& keyUpEvent);

    private:
        Registry* RegistryPtr;
        EventBus* EventBusPtr;

    private:
        void OnSystemRemoved() override;
    };
}
