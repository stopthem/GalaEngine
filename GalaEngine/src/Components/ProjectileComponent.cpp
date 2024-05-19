#include "ProjectileComponent.h"

namespace gala
{
    ProjectileParams::ProjectileParams(const glm::vec2 projectileVector, const bool isFriendly, const double damageAmount, const int lifetimeMiliseconds)
        :ProjectileVector(projectileVector), LifetimeMiliSeconds(lifetimeMiliseconds), IsFriendly(isFriendly), DamageAmount(damageAmount)
    {
    }

    ProjectileComponent::ProjectileComponent(const ProjectileParams& projectileParams)
        :IsFriendly(projectileParams.IsFriendly), DamageAmount(projectileParams.DamageAmount)
    {

    }
}
