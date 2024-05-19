#pragma once
#include <nlohmann/json.hpp>

namespace gala
{
    /*
 * LifetimeComponent
 *
 * Component that holds information about lifetime and current timer in miliseconds.
 */
    struct LifetimeComponent
    {
    public:
        explicit LifetimeComponent(int lifetimeMiliSeconds = 5000);

        LifetimeComponent(const LifetimeComponent& lifetimeComponent) = default;

    public:
        int LifetimeMiliSeconds;

        int CurrentTimerMiliSeconds = 0;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(LifetimeComponent, LifetimeMiliSeconds)
    };
}
