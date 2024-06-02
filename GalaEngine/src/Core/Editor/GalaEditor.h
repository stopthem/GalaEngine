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

        [[nodiscard]] Entity GetSelectedEntity()const
        {
            return SelectedEntity;
        }

        void ClearSelectedEntity();

    private:
        bool HasSelectedEntity = false;

        Entity SelectedEntity;

    public:
        void Update();
    };
}
