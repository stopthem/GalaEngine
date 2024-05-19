#include "CollisionEvent.h"

namespace gala
{
    CollisionEvent::CollisionEvent(const Entity sourceEntity, const Entity targetEntity)
        : SourceEntity(sourceEntity),TargetEntity(targetEntity)
    {
    }
}
