#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(sol::function function)
	:Function(std::move(function))
{
}
