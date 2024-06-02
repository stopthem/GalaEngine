#pragma once

#include "../../Core/Editor/GalaEditor.h"
#include "../../ECS/ECS.h"

namespace gala
{
    class KeyUpEvent;

    /*
* RenderLevelHierarchyGUISystem
*
*
*/
    class RenderLevelHierarchyGUISystem : public System
    {
    public:
        explicit RenderLevelHierarchyGUISystem(GalaEditor* galaEditor);

    public:
        void Update(const std::unique_ptr<Registry>& registry) const;

    private:
        GalaEditor* GalaEditorPtr = nullptr;
    };
}
