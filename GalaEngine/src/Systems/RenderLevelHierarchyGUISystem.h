#pragma once

#include "../Core/Editor/GalaEditor.h"
#include "../ECS/ECS.h"
#include "../EventBus/EventBus.h"

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
        RenderLevelHierarchyGUISystem(GalaEditor* galaEditor, EventBus* eventBus);

    public:
        void Update(const std::unique_ptr<Registry>& registry) const;

        void OnSystemRemoved() override;

    private:
        void OnKeyboardKeyPressed(KeyUpEvent& keyPressedEvent);

    private:
        GalaEditor* GalaEditorPtr = nullptr;

        EventBus* EventBusPtr = nullptr;
    };
}
