#include "LifetimeSystem.h"
#include "../Components/LifetimeComponent.h"

LifetimeSystem::LifetimeSystem(Registry* registry)
	:RegistryPtr(registry)
{
	RequireComponent<LifetimeComponent>();
}

void LifetimeSystem::Update(const double deltaTime) const
{
	std::vector<Entity> entities = GetSystemEntities();

	for (auto it = entities.begin(); it != entities.end();)
	{
		Entity systemEntity = *it;
		auto& lifetimeComponent = systemEntity.GetComponent<LifetimeComponent>();

		lifetimeComponent.CurrentTimerMiliSeconds += static_cast<int>(deltaTime * 1000.0);

		if (lifetimeComponent.CurrentTimerMiliSeconds >= lifetimeComponent.LifetimeMiliSeconds)
		{
			RegistryPtr->KillEntity(systemEntity);
			it = entities.erase(it);
		}
		else
		{
			++it;
		}
	}
}
