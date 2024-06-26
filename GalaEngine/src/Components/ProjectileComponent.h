#pragma once
#include "glm/vec2.hpp"

namespace gala
{
    /*
 * ProjectileParams
 *
 * Struct that holds information about the projectile parameters.
 */
    struct ProjectileParams
    {
    public:
        explicit ProjectileParams(glm::vec2 projectileVector = glm::vec2(0), bool isFriendly = false, double damageAmount = 10, int lifetimeMiliseconds = 5000);

    public:
        glm::vec2 ProjectileVector;

        int LifetimeMiliSeconds;

        bool IsFriendly;

        double DamageAmount;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ProjectileParams, ProjectileVector, LifetimeMiliSeconds, IsFriendly, DamageAmount)
    };

    /*
 * ProjectileComponent
 *
 * Component that holds information about damage and is friendly.
 * Can be used to define a entity is a projectile or not.
 */
    struct ProjectileComponent
    {
    public:
        explicit ProjectileComponent(const ProjectileParams& projectileParams = ProjectileParams());

        ProjectileComponent(const ProjectileComponent& profProjectileComponent) = default;
    public:
        bool IsFriendly;
        double DamageAmount;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(ProjectileComponent, IsFriendly, DamageAmount)
    };
}
