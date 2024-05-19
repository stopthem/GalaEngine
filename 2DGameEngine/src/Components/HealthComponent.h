#pragma once
#include <nlohmann/json.hpp>

namespace gala
{
    /*
 * HealthComponent
 *
 * Component that holds information about health.
 */
    struct HealthComponent
    {
    public:
        explicit HealthComponent(double health = 100.0);

        HealthComponent(const HealthComponent& healthComponent) = default;

    public:
        double StartingHealth;
        double Health;

    public:
        [[nodiscard]] double GetHealthNormalized() const { return Health / StartingHealth; }

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(HealthComponent, StartingHealth);
    };
}
