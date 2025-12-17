#include "StagePanel.hpp"

#include "../../Renderer.hpp"

#include <imgui.h>

#include <string>

void StagePanel::render()
{
	ImGui::Begin("StageView");

	ImVec2 size = ImGui::GetContentRegionAvail();
	ImGui::Text((std::to_string(size.x) + " " + std::to_string(size.y)).c_str());

	ImGui::End();
}

void StagePanel::OnNotify(Event event)
{
}