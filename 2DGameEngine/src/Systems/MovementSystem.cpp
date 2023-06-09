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
	for (Entity& entity : GetSystemEntities())
	{
		auto& transformComponent = entity.GetComponent<TransformComponent>();
		const auto rigidbodyComponent = entity.GetComponent<RigidbodyComponent>();

		transformComponent.Position += rigidbodyComponent.Velocity * static_cast<float>(deltaTime);
	}
}
