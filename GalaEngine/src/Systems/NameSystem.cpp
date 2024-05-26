#include "NameSystem.h"

#include "../Components/NameComponent.h"

gala::NameSystem::NameSystem()
{
    RequireComponent<NameComponent>();
}

void gala::NameSystem::SetNameOfEntity(Entity entity, const std::string& name) const
{
    assert(entity.HasComponent<NameComponent>());
    
    NameComponent& nameComponent = entity.GetComponent<NameComponent>();

    nameComponent.Name = name;
}
