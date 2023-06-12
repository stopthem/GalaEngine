#include "MovementSystem.h"
#include <string>
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Logger/Logger.h"

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

		Logger::Log("entity with id current y " + std::to_string(transformComponent.Location.y) + " velocity y " + std::to_string(rigidbodyComponent.Velocity.y));
		transformComponent.Location += rigidbodyComponent.Velocity * static_cast<float>(deltaTime);
	}
}
