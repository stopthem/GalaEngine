#pragma once

#include "../../Core/Editor/GalaEditor.h"
#include "../../ECS/ECS.h"

namespace gala
{
    /*
* RenderEntityDetailsSystem
*
*  
*/
    class RenderEntityDetailsSystem : public System
    {
    public:
        explicit RenderEntityDetailsSystem(GalaEditor* galaEditor);

    private:
        GalaEditor* GalaEditorPtr = nullptr;

    public:
        void Update();
    };
}
