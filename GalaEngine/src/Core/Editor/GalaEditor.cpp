#include "GalaEditor.h"

namespace gala
{
    void GalaEditor::SetSelectedEntity(Entity entity)
    {
        HasSelectedEntity = true;
        SelectedEntity = entity;
    }
}
