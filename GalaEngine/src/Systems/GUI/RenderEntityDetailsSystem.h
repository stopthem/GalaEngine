#pragma once

#include <imgui/ImGuiNotify.hpp>

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

        int TreeNodeFlags = ImGuiTreeNodeFlags_DefaultOpen;

    public:
        void Update();

    private:
        // Begin component imgui are of given TComponent.
        // Will create a TreeNodeEx and a Add Component button
        template <typename TComponent>
        void BeginComponentArea(const std::string& label, const std::function<void()>& onTreeNodeSelected, bool canRemove = true) const;
    };

    template <typename TComponent>
    void RenderEntityDetailsSystem::BeginComponentArea(const std::string& label, const std::function<void()>& onTreeNodeSelected,
                                                       bool canRemove) const
    {
        // Store selected entity
        Entity selectedEntity = GalaEditorPtr->GetSelectedEntity();

        // Space between components
        ImGui::Dummy({0, 10});
        ImGui::SeparatorEx(ImGuiSeparatorFlags_Horizontal);
        ImGui::Dummy({0, 10});

        // We will draw component if entity has it
        if (selectedEntity.HasComponent<TComponent>())
        {
            bool treeNodeSelected = false;
            if (ImGui::TreeNodeEx(label.c_str(), TreeNodeFlags))
            {
                treeNodeSelected = true;
            }

            if (canRemove)
            {
                // Add remove component button
                ImGui::SameLine();
                ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 50);
                ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
                if (ImGui::Button(ICON_FA_XMARK))
                {
                    selectedEntity.RemoveComponent<TComponent>();
                }
            }
            else if (treeNodeSelected)
            {
                // Notify caller that we have a successful interaction in tree node
                onTreeNodeSelected();
            }

            ImGui::TreePop();
        }
        else if (ImGui::Button(std::string("Add " + label).c_str())) // If entity doesn't have related component, add "Add Component" button
        {
            selectedEntity.AddComponent<TComponent>();
        }
    }
}
