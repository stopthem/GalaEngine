#include "ScriptSystem.h"
#include <SDL_timer.h>
#include "../Components/ScriptComponent.h"
#include "../ECS/ECS.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Logger/Logger.h"

namespace gala
{
    void SetEntityLocation(Entity entity, const double x, const double y)
    {
        if (!entity.HasComponent<TransformComponent>())
        {
            Logger::Log("Trying to set location of an entity that has no TransformComponent!");
            return;
        }

        auto& transformComponent = entity.GetComponent<TransformComponent>();
        transformComponent.Location = {x, y};
    }

    std::tuple<double, double> GetEntityLocation(Entity entity)
    {
        if (!entity.HasComponent<TransformComponent>())
        {
            Logger::Log("Trying to get location of an entity that has no TransformComponent!");
            return {0, 0};
        }

        const auto transformComponent = entity.GetComponent<TransformComponent>();
        return {transformComponent.Location.x, transformComponent.Location.y};
    }

    std::tuple<double, double> GetEntityVelocity(Entity entity)
    {
        if (!entity.HasComponent<RigidbodyComponent>())
        {
            Logger::Log("Trying to get velocity of an entity that has no RigidbodyComponent!");
            return {0, 0};
        }

        const auto rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();
        return {rigidbodyComponent.Velocity.x, rigidbodyComponent.Velocity.y};
    }

    void SetEntityVelocity(Entity entity, const double x, const double y)
    {
        if (!entity.HasComponent<RigidbodyComponent>())
        {
            Logger::Log("Trying to set velocity of an entity that has no RigidbodyComponent!");
            return;
        }

        auto& rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();
        rigidbodyComponent.Velocity = {x, y};
    }

    void SetEntityRotation(Entity entity, const double angle)
    {
        if (!entity.HasComponent<TransformComponent>())
        {
            Logger::Log("Trying to set rotation of an entity that has no TransformComponent!");
            return;
        }

        auto& transformComponent = entity.GetComponent<TransformComponent>();
        transformComponent.Angle = angle;
    }

    double GetEntityRotation(Entity entity)
    {
        if (!entity.HasComponent<TransformComponent>())
        {
            Logger::Log("Trying to get rotation of an entity that has no TransformComponent!");
            return 0;
        }

        const auto transformComponent = entity.GetComponent<TransformComponent>();
        return transformComponent.Angle;
    }

    void SetEntityAnimationFrame(Entity entity, int frame)
    {
        if (!entity.HasComponent<AnimationComponent>())
        {
            Logger::Log("Trying to set animation frame of an entity that has no AnimationComponent!");
            return;
        }

        auto& animationComponent = entity.GetComponent<AnimationComponent>();
        animationComponent.CurrentFrame = frame;
    }

    void SetEntityProjectileVelocity(Entity entity, const double x, const double y)
    {
        if (!entity.HasComponent<ProjectileEmitterComponent>())
        {
            Logger::Log("Trying to set projectile velocity of an entity that has no ProjectileEmitterComponent!");
            return;
        }

        auto& projectileEmitterComponent = entity.GetComponent<ProjectileEmitterComponent>();
        projectileEmitterComponent.EmitterProjectileParams.ProjectileVector = {x, y};
    }

    ScriptSystem::ScriptSystem(sol::state_view luaState)
        : Lua(std::move(luaState))
    {
        RequireComponent<ScriptComponent>();

        CreateLuaBindings();
    }

    void ScriptSystem::Update(const double deltaTime)
    {
        ForEachSystemEntity([&](Entity systemEntity)
        {
            auto& scriptComponent = systemEntity.GetComponent<ScriptComponent>();

            scriptComponent.Function(systemEntity, deltaTime, SDL_GetTicks());
        });
    }

    void ScriptSystem::CreateLuaBindings()
    {
        Lua.new_usertype<Entity>(
            "entity",
            "get_id", &Entity::GetId,
            "kill", &Entity::Kill,
            "has_tag", &Entity::HasTag,
            "in_group", &Entity::InGroup
        );

        Lua.set_function("set_location", SetEntityLocation);
        Lua.set_function("get_location", GetEntityLocation);
        Lua.set_function("set_velocity", SetEntityVelocity);
        Lua.set_function("get_velocity", GetEntityVelocity);
        Lua.set_function("set_projectile_velocity", SetEntityProjectileVelocity);
        Lua.set_function("set_animation_frame", SetEntityAnimationFrame);
        Lua.set_function("get_rotation", GetEntityRotation);
        Lua.set_function("set_rotation", SetEntityRotation);
    }
}
