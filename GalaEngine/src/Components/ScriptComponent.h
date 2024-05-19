#pragma once
#include <nlohmann/json.hpp>

#include "sol/sol.hpp"

namespace gala
{
    struct ScriptComponent
    {
    public:
        explicit ScriptComponent(sol::function function = sol::lua_nil);

        ScriptComponent(const ScriptComponent& scriptComponent) = default;

    public:
        sol::function Function;

#pragma region Serialization

    private:
        uint8_t EmptyIntForSerialization = 0;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScriptComponent, EmptyIntForSerialization)
#pragma endregion
    };
}
