#pragma once

#include "../src/ECS/ECS.h"

namespace gala
{
    class GalaEditor
    {
    public:
        GalaEditor() = default;

    public:
        void SetSelectedEntity(Entity entity);

        [[nodiscard]] bool TryGetSelectedEntity(Entity& outSelectedEntity) const
        {
            outSelectedEntity = SelectedEntity;

            return HasSelectedEntity;
        }

    private:
        bool HasSelectedEntity = false;

        Entity SelectedEntity;
    };
}
