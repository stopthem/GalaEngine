#include "ScriptComponent.h"

namespace gala
{
    ScriptComponent::ScriptComponent(sol::function function)
        :Function(std::move(function))
    {
    }
}
