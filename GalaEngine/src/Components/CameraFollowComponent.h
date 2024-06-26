#pragma once
#include <nlohmann/json.hpp>

namespace gala
{
    /*
 * CameraFollowComponent
 *
 * Component used to make camera follow the transform of the entity.
 */
    struct CameraFollowComponent
    {
    public:
        CameraFollowComponent() = default;

        CameraFollowComponent(const CameraFollowComponent& cameraFollowComponent) = default;

#pragma region Serialization

    private:
        uint8_t EmptyIntForSerialization = 0;

    public:
        NLOHMANN_DEFINE_TYPE_INTRUSIVE(CameraFollowComponent, EmptyIntForSerialization)
#pragma endregion
    };
}
