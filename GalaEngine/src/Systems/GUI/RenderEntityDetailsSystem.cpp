#include "RenderEntityDetailsSystem.h"

#include "../../Components/AnimationComponent.h"
#include "../../Components/BoxColliderComponent.h"
#include "../../Components/CameraFollowComponent.h"
#include "../../Components/HealthBarComponent.h"
#include "../../Components/HealthComponent.h"
#include "../../Components/NameComponent.h"
#include "../../Components/TransformComponent.h"
#include "../../Game/Game.h"
#include "imgui/imgui.h"
#include "imgui/imgui_internal.h"

gala::RenderEntityDetailsSystem::RenderEntityDetailsSystem(GalaEditor* galaEditor)
    : GalaEditorPtr(galaEditor)
{
}

void gala::RenderEntityDetailsSystem::Update()
{
    ImGui::Begin("Details", nullptr, ImGuiWindowFlags_NoCollapse);

    // If first use ever, show window at far right
    ImGui::SetWindowPos({static_cast<float>(Game::WindowWidth - 500), 0}, ImGuiCond_FirstUseEver);
    ImGui::SetWindowSize({500, static_cast<float>(Game::WindowHeight)}, ImGuiCond_FirstUseEver);

    Entity selectedEntity;
    if (!GalaEditorPtr->TryGetSelectedEntity(selectedEntity))
    {
        ImGui::End();
        return;
    }

    ImGui::Spacing();

    // Name
    {
        if (char* buf = selectedEntity.GetComponent<NameComponent>().Name.data();
            ImGui::InputText("Name", buf, 256, ImGuiInputTextFlags_EnterReturnsTrue | ImGuiInputTextFlags_AutoSelectAll)
            && std::strlen(buf))
        {
            selectedEntity.GetComponent<NameComponent>().Name = buf;
        }
    }

    // ID
    {
        ImGui::BeginDisabled();
        ImGui::Text(std::format("Id: {}", selectedEntity.GetId()).c_str());
        ImGui::EndDisabled();
    }

    // Space between upper elements and components
    ImGui::Dummy({0, 100});

    // Components
    {
        ImGui::BeginChild("Components");

        if (ImGui::CollapsingHeader("Components", ImGuiTreeNodeFlags_DefaultOpen))
        {
            BeginComponentArea<TransformComponent>("Transform Component", [selectedEntity]
            {
                TransformComponent& transformComponent = selectedEntity.GetComponent<TransformComponent>();

                if (float locations[2] = {transformComponent.Location.x, transformComponent.Location.y};
                    ImGui::InputFloat2("Location", locations))
                {
                    transformComponent.Location = {locations[0], locations[1]};
                }
            }, false);

            BeginComponentArea<AnimationComponent>("Animation Component", [selectedEntity]
            {
                AnimationComponent& animationComponent = selectedEntity.GetComponent<AnimationComponent>();

                ImGui::InputInt("Frame Speed Rate", &animationComponent.FrameSpeedRate);
            });

            BeginComponentArea<BoxColliderComponent>("Box Collider Component", [selectedEntity]
            {
                BoxColliderComponent& boxColliderComponent = selectedEntity.GetComponent<BoxColliderComponent>();

                ImGui::InputInt("Width", &boxColliderComponent.Width);
                ImGui::InputInt("Height", &boxColliderComponent.Height);

                if (float offset[] = {boxColliderComponent.Offset.x, boxColliderComponent.Offset.y}; ImGui::InputFloat2("Offset", offset))
                {
                    boxColliderComponent.Offset = {offset[0], offset[1]};
                }
            });

            BeginComponentArea<CameraFollowComponent>("Camera Follow Component", [selectedEntity]
            {
                CameraFollowComponent& cameraFollowComponent = selectedEntity.GetComponent<CameraFollowComponent>();
            });

            BeginComponentArea<HealthBarComponent>("Health Bar Component", [selectedEntity]
            {
                HealthBarComponent& healthBarComponent = selectedEntity.GetComponent<HealthBarComponent>();
            });

            BeginComponentArea<HealthComponent>("Health Component", [selectedEntity]
            {
                HealthComponent& healthComponent = selectedEntity.GetComponent<HealthComponent>();
                ImGui::InputDouble("Starting Health", &healthComponent.StartingHealth);

                ImGui::BeginDisabled();
                ImGui::InputDouble("Health", &healthComponent.Health);
                ImGui::EndDisabled();
            });

            // if (KeyboardControlledComponent keyboardControlledComponent; selectedEntity.TryGetComponent<KeyboardControlledComponent>(keyboardControlledComponent))
            // {
            //     nlohmann::json j = {typeid(KeyboardControlledComponent).name(), keyboardControlledComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (LifetimeComponent lifetimeComponent; selectedEntity.TryGetComponent<LifetimeComponent>(lifetimeComponent))
            // {
            //     nlohmann::json j = {typeid(LifetimeComponent).name(), lifetimeComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (ProjectileComponent projectileComponent; selectedEntity.TryGetComponent<ProjectileComponent>(projectileComponent))
            // {
            //     nlohmann::json j = {typeid(ProjectileComponent).name(), projectileComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (ScriptComponent scriptComponent; selectedEntity.TryGetComponent<ScriptComponent>(scriptComponent))
            // {
            //     nlohmann::json j = {typeid(ScriptComponent).name(), scriptComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (ProjectileEmitterComponent projectileEmitterComponent; selectedEntity.TryGetComponent<ProjectileEmitterComponent>(projectileEmitterComponent))
            // {
            //     nlohmann::json j = {typeid(ProjectileEmitterComponent).name(), projectileEmitterComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (RigidbodyComponent rigidbodyComponent; selectedEntity.TryGetComponent<RigidbodyComponent>(rigidbodyComponent))
            // {
            //     nlohmann::json j = {typeid(RigidbodyComponent).name(), rigidbodyComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (ShootingComponent shootingComponent; selectedEntity.TryGetComponent<ShootingComponent>(shootingComponent))
            // {
            //     nlohmann::json j = {typeid(ShootingComponent).name(), shootingComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (SpriteComponent spriteComponent; selectedEntity.TryGetComponent<SpriteComponent>(spriteComponent))
            // {
            //     nlohmann::json j = {typeid(SpriteComponent).name(), spriteComponent};
            //     selectedEntityJson.push_back(j);
            // }
            //
            // if (TextComponent textComponent; selectedEntity.TryGetComponent<TextComponent>(textComponent))
            // {
            //     nlohmann::json j = {typeid(TextComponent).name(), textComponent};
            //     selectedEntityJson.push_back(j);
            // }
        }


        ImGui::EndChild();
    }

    ImGui::End();
}
