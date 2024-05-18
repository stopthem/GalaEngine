#pragma once

#include "../ECS/ECS.h"

class KeyUpEvent;
class ProjectileEmitterSystem;
class EventBus;

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
