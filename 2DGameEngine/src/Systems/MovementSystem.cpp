#include "MovementSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../EventBus/EventBus.h"
#include "../Game/Game.h"

MovementSystem::MovementSystem(EventBus* eventBus)
	:EventBusPtr(eventBus)
{
	RequireComponent<TransformComponent>();
	RequireComponent<RigidbodyComponent>();

	eventBus->SubscribeToEvent<CollisionEvent>(this, &MovementSystem::OnCollision);
}

MovementSystem::~MovementSystem() = default;

void MovementSystem::Update(const double deltaTime) const
{
	for (Entity& entity : GetSystemEntities())
	{
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		const auto rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();

		const glm::vec2 targetLocation = transformComponent.Location + rigidbodyComponent.Velocity * static_cast<float>(deltaTime);

		constexpr int playerXBoundInc = 20;
		constexpr int playerYBoundInc = 20;
		// Is entity player and target location is not within map bounds ?
		if ((targetLocation.x + playerXBoundInc > Game::MapWidth ||
			targetLocation.x - playerXBoundInc < 0 ||
			targetLocation.y + playerYBoundInc > Game::MapHeight ||
			targetLocation.y - playerYBoundInc < 0) && entity.HasTag(TAG_PLAYER))
		{
			continue;
		}
		transformComponent.Location = targetLocation;
	}
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
		// return because we want to reverse our angle and velocity if we facing the target.
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
