#pragma once

#include "../ECS/ECS.h"

namespace gala
{
    /*
* 
*
*
*/
    class NameSystem : public System
    {
    public:
        NameSystem();

    public:
        void SetNameOfEntity(Entity entity, const std::string& name) const;
    };
}
