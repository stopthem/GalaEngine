#pragma once
#include <nlohmann/json.hpp>

#include "../Core/UUID.h"

/*
 * UUIDComponent
 *
 * Component that hols a unique id
 */
struct UuidComponent
{
public:
    UuidComponent() = default;

public:
    Uuid Uuid;

public:
    NLOHMANN_DEFINE_TYPE_INTRUSIVE(UuidComponent, Uuid)
};
