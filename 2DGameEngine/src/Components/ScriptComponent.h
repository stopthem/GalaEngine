#pragma once
#include "sol/sol.hpp"

struct ScriptComponent
{
public:
	explicit ScriptComponent(sol::function function = sol::lua_nil);

public:
	sol::function Function;
};

