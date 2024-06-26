#pragma once

#include "../ECS/ECS.h"
#include "../EventBus/Event.h"

namespace gala
{
    class CollisionEvent : public Event
    {
    public:
        CollisionEvent(Entity sourceEntity, Entity targetEntity);

    public:
        Entity SourceEntity;
        Entity TargetEntity;
    };
}

