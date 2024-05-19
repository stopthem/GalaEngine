#pragma once

#include "../ECS/ECS.h"
#include <sol/sol.hpp>

namespace gala
{
    class ScriptSystem : public System
    {
    public:
        explicit ScriptSystem(sol::state_view luaState);

        ScriptSystem(ScriptSystem& scriptSystem) = default;
    public:
        void Update(double deltaTime);

    private:
        sol::state_view Lua = nullptr;

        void CreateLuaBindings();
    };
}

