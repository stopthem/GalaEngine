#include "RenderLevelHierarchyGUISystem.h"

#include "../Components/NameComponent.h"
#include "../Events/KeyUpEvent.h"
#include "../Game/Game.h"
#include "imgui/imgui.h"

namespace gala
{
    RenderLevelHierarchyGUISystem::RenderLevelHierarchyGUISystem(GalaEditor* galaEditor, EventBus* eventBus)
        : GalaEditorPtr(galaEditor), EventBusPtr(eventBus)
    {
        eventBus->SubscribeToEvent<KeyUpEvent>(this, &RenderLevelHierarchyGUISystem::OnKeyboardKeyPressed);
    }

    void RenderLevelHierarchyGUISystem::Update(const std::unique_ptr<Registry>& registry) const
    {
        ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowPos({0, static_cast<float>(Game::WindowHeight) - 300}, ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize({350, 300}, ImGuiCond_FirstUseEver);

        registry->ForEachEntity([&](Entity entity)
        {
            const NameComponent nameComponent = entity.GetComponent<NameComponent>();
            ImGui::TreeNodeEx(nameComponent.Name.c_str(), ImGuiTreeNodeFlags_Leaf);

            if (ImGui::IsMouseDown(ImGuiMouseButton_Left))
            {
                GalaEditorPtr->SetSelectedEntity(entity);
                Logger::Log(std::format("entity with id {} is selected",entity.GetId()));
            }

            ImGui::Separator();

            ImGui::TreePop();
        });


        ImGui::End();
    }

    void RenderLevelHierarchyGUISystem::OnSystemRemoved()
    {
        System::OnSystemRemoved();

        EventBusPtr->UnSubscribeFromEvent<KeyUpEvent>(this, &RenderLevelHierarchyGUISystem::OnKeyboardKeyPressed);
    }

    void RenderLevelHierarchyGUISystem::OnKeyboardKeyPressed(KeyUpEvent& keyPressedEvent)
    {
        
    }
}
