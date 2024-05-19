#include "MovementSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
#include "../EventBus/EventBus.h"
#include "../Game/Game.h"

namespace gala
{
    MovementSystem::MovementSystem(EventBus* eventBus)
        : EventBusPtr(eventBus)
    {
        RequireComponent<TransformComponent>();
        RequireComponent<RigidbodyComponent>();

        eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
    }

    MovementSystem::~MovementSystem() = default;

    void MovementSystem::Update(const double deltaTime, const std::unique_ptr<Registry>& registry)
    {
        ForEachSystemEntity([&](Entity systemEntity)
        {
            auto& transformComponent = systemEntity.GetComponent<TransformComponent>();
            const auto rigidbodyComponent = systemEntity.GetComponent<RigidbodyComponent>();
            
            transformComponent.Location = transformComponent.Location + rigidbodyComponent.Velocity * static_cast<float>(deltaTime);
        });
    }

    void MovementSystem::OnCollision(CollisionEvent& collisionEvent)
    {
        auto CheckEnemyHitObstacle = [](Entity sourceEntity, Entity targetEntity)
        {
            if (!sourceEntity.InGroup(GROUP_ENEMY))
            {
                return;
            }

            if (!targetEntity.InGroup(GROUP_OBSTACLE))
            {
                return;
            }

            const auto targetTransform = targetEntity.GetComponent<TransformComponent>();

            auto& sourceRigidbody = sourceEntity.GetComponent<RigidbodyComponent>();
            auto& sourceTransform = sourceEntity.GetComponent<TransformComponent>();

            // Does our source entity's velocity dot direction from source to target is more than 15,
            // return because we want to reverse our angle and velocity if we're facing the target.
            const glm::vec2 sourceToTargetDirection = glm::normalize(targetTransform.Location - sourceTransform.Location);
            if (std::abs(glm::dot(glm::normalize(sourceRigidbody.Velocity), sourceToTargetDirection)) > 15)
            {
                return;
            }

            sourceTransform.Angle *= -1;

            sourceRigidbody.Velocity *= -1;
        };

        CheckEnemyHitObstacle(collisionEvent.SourceEntity, collisionEvent.TargetEntity);
        CheckEnemyHitObstacle(collisionEvent.TargetEntity, collisionEvent.SourceEntity);
    }

    void MovementSystem::OnSystemRemoved()
    {
        System::OnSystemRemoved();
        EventBusPtr->UnSubscribeFromEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
    }
}
