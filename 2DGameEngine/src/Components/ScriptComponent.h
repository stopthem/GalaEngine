#pragma once
#include <nlohmann/json.hpp>

#include "sol/sol.hpp"

struct ScriptComponent
{
public:
    explicit ScriptComponent(sol::function function = sol::lua_nil);

public:
    sol::function Function;

#pragma region Serialization

private:
    uint8_t EmptyIntForSerialization = 0;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(ScriptComponent, EmptyIntForSerialization)
#pragma endregion
};
