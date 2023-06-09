#include "MovementSystem.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"

MovementSystem::MovementSystem()
{
	RequireComponent<TransformComponent>();
	RequireComponent<RigidbodyComponent>();
}

MovementSystem::~MovementSystem() = default;

void MovementSystem::Update(const double deltaTime) const
{
	for (Entity entity : GetSystemEntities())
	{
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		const RigidbodyComponent rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();

		transformComponent.Position += rigidbodyComponent.Velocity * static_cast<float>(deltaTime);

		Logger::Log("Entity id = " + std::to_string(entity.GetId())
			+ "position = x: " + std::to_string(transformComponent.Position.x) + " y: " + std::to_string(transformComponent.Position.y));
	}
}
