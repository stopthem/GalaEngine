#include "MovementSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/SpriteComponent.h"
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

void MovementSystem::Update(const double deltaTime, const std::unique_ptr<Registry>& registry) const
{
	for (Entity& entity : GetSystemEntities())
	{
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		const auto rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();

		const glm::vec2 targetLocation = transformComponent.Location + rigidbodyComponent.Velocity * static_cast<float>(deltaTime);

		// Returns if targetLocation with given bounds is inside or outside.
		auto IsNotInMap = [&targetLocation](const glm::vec2 bound, bool inwards = true)
		{
			const glm::vec2 actualBound = { bound.x * (inwards ? 1 : -1) , bound.y * (inwards ? 1 : -1) };
			return (targetLocation.x + bound.x > Game::MapWidth ||
				targetLocation.x - bound.x < 0 ||
				targetLocation.y + bound.y > Game::MapHeight ||
				targetLocation.y - bound.y < 0);
		};

		// Is entity player and target location is not within map bounds ?
		if (IsNotInMap(glm::vec2(20, 20)) && entity.HasTag(TAG_PLAYER))
		{
			continue;
		}

		glm::vec2 entityBoundCheck = glm::vec2(0);
		// If we have a sprite, check if the entity is completely outside map bounds to kill.
		if (entity.HasComponent<SpriteComponent>())
		{
			const auto spriteComponent = entity.GetComponent<SpriteComponent>();

			entityBoundCheck = { spriteComponent.Width,spriteComponent.Height };
		}
		if (IsNotInMap(entityBoundCheck, false))
		{
			registry->KillEntity(entity);
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
