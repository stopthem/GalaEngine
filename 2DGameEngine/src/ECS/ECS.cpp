#include "ECS.h"
#include <bitset>

Entity::Entity(int id)
	:id(id)
{
}

void System::AddEntityToSystem(Entity entity)
{
	// Does entities contain given entity ?
	if (std::find(entities.begin(), entities.end(), entity) == entities.end())
	{
		return;
	}

	// If not push it.
	entities.push_back(entity);
}

void System::RemoveEntityFromSystem(Entity entity)
{
	entities.erase(std::remove_if(entities.begin(), entities.end()
		, [&entity](Entity otherEntity)
		{
			return entity == otherEntity;
		})
		, entities.end());
}
