#include "RenderGUISystem.h"
#include <imgui/imgui.h>
#include <imgui/imgui_impl_sdl2.h>
#include <imgui/imgui_sdl.h>
#include "glm/vec2.hpp"
#include "../Components/ProjectileComponent.h"
#include "../Components/TransformComponent.h"
#include "../Components/RigidbodyComponent.h"
#include "../Components/HealthComponent.h"
#include "../Components/ProjectileEmitterComponent.h"
#include "../Components/BoxColliderComponent.h"
#include "../Components/HealthBarComponent.h"
#include "../Components/SpriteComponent.h"


void RenderGUISystem::Update(const std::unique_ptr<Registry>& registry) const
{
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("Spawn enemies");

	static int inputV[2];
	ImGui::InputInt2("Enemy location", inputV);

	if (ImGui::Button("Spawn Enemy"))
	{
		Entity enemy = registry->CreateEntity();
		enemy.AddComponent<RigidbodyComponent>(glm::vec2(0, 0));
		enemy.AddComponent<TransformComponent>(glm::vec2(inputV[0], inputV[1]), glm::vec2(2), 0);
		enemy.AddComponent<SpriteComponent>("tank-image", 32, 32, 1, false, true);
		enemy.AddComponent<BoxColliderComponent>(32, 32);
		enemy.AddComponent<ProjectileEmitterComponent>(ProjectileParams(glm::vec2(50, 0), false, 5), 3000);
		enemy.AddComponent<HealthComponent>(50);
		enemy.AddComponent<HealthBarComponent>();
		enemy.AddToGroup(GROUP_ENEMY);
	}

	ImGui::End();

	ImGui::Render();
	ImGuiSDL::Render(ImGui::GetDrawData());
}
