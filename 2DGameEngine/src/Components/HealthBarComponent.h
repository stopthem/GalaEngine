#pragma once
#include <nlohmann/json.hpp>


/*
 * HealthBarComponent
 *
 * Component that used to detect health bar wanted entities.
 */
struct HealthBarComponent
{
public:
    HealthBarComponent() = default;

#pragma region Serialization

private:
    uint8_t EmptyIntForSerialization = 0;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(HealthBarComponent, EmptyIntForSerialization)
#pragma endregion
};
