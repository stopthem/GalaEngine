#include "GalaEditor.h"

namespace gala
{
    void GalaEditor::SetSelectedEntity(const Entity entity)
    {
        HasSelectedEntity = true;
        SelectedEntity = entity;
    }

    void GalaEditor::ClearSelectedEntity()
    {
        HasSelectedEntity = false;
    }

    void GalaEditor::Update()
    {
        if (HasSelectedEntity && !SelectedEntity.IsValid())
        {
            ClearSelectedEntity();
        }
    }
}
