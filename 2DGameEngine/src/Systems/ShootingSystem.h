#pragma once

#include "../ECS/ECS.h"

class KeyPressedEvent;
class ProjectileEmitterSystem;
class EventBus;
class ShootingSystem : public System
{
public:
	explicit ShootingSystem(Registry* registry, EventBus* eventBus);

public:
	void OnKeyPressed(KeyPressedEvent& keyPressedEvent);

private:
	Registry* RegistryPtr;
	EventBus* EventBusPtr;

private:
	void OnSystemRemoved() override;
};

