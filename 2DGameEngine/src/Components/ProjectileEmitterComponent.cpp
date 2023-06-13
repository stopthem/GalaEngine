#include "ProjectileEmitterComponent.h"
#include <SDL_timer.h>

ProjectileEmitterComponent::ProjectileEmitterComponent(const glm::vec2 projectileVector, const int projectileEmittingInterval, const bool isFriendly, const double damageAmount, const int lifetimeMiliseconds)
	: ProjectileVector(projectileVector), ProjectileEmittingInterval(projectileEmittingInterval), LifetimeMiliSeconds(lifetimeMiliseconds), IsFriendly(isFriendly), DamageAmount(damageAmount)
{
	LastEmittedTime = static_cast<int>(SDL_GetTicks());
}
