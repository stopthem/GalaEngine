#include "RenderLevelHierarchyGUISystem.h"

#include <imgui/IconsFontAwesome6.h>

#include "../../Components/NameComponent.h"
#include "../../Game/Game.h"
#include "imgui/imgui.h"

namespace gala
{
    RenderLevelHierarchyGUISystem::RenderLevelHierarchyGUISystem(GalaEditor* galaEditor)
        : GalaEditorPtr(galaEditor)
    {
    }

    void RenderLevelHierarchyGUISystem::Update(const std::unique_ptr<Registry>& registry) const
    {
        ImGui::Begin("Hierarchy", nullptr, ImGuiWindowFlags_NoCollapse);

        // Create Entity Button
        if (ImGui::Button("Create Entity"))
        {
            const Entity createdEntity = registry->CreateEntity();
            GalaEditorPtr->SetSelectedEntity(createdEntity);
        }

        // Separator and space between buttons and entities
        ImGui::Separator();
        ImGui::Dummy({0, 10});

        // If first use ever, show window at bottom left corner
        ImGui::SetWindowPos({0, static_cast<float>(Game::WindowHeight) - 500}, ImGuiCond_FirstUseEver);
        ImGui::SetWindowSize({350, 500}, ImGuiCond_FirstUseEver);

        registry->ForEachEntity([&](const Entity entity)
        {
            ImGuiTreeNodeFlags treeNodeFlags = ImGuiTreeNodeFlags_Leaf;

            // If current iterated entity is selected entity, mark it as selected
            if (Entity selectedEntity; GalaEditorPtr->TryGetSelectedEntity(selectedEntity) && selectedEntity == entity)
            {
                treeNodeFlags |= ImGuiTreeNodeFlags_Selected;
            }

            // Create the actual entity item in imgui
            const NameComponent nameComponent = entity.GetComponent<NameComponent>();
            ImGui::TreeNodeEx(nameComponent.Name.c_str(), treeNodeFlags);

            // If item is clicked in imgui, set currently iterated entity as selected
            if (ImGui::IsItemClicked())
            {
                GalaEditorPtr->SetSelectedEntity(entity);
            }

            ImGui::SameLine();
            ImGui::SetCursorPosX(ImGui::GetWindowSize().x - 50);
            ImGui::SetCursorPosY(ImGui::GetCursorPosY() - 5);
            if (ImGui::Button(ICON_FA_XMARK))
            {
                entity.Kill();
            }

            // A separator between tree nodes
            ImGui::Separator();

            ImGui::TreePop();
        });


        ImGui::End();
    }
}
