#include "StagePanel.hpp"

#include "../../Renderer.hpp"

#include "../../../Utility/Utils.hpp"

#include <imgui.h>

#include <string>

void StagePanel::render()
{
	ImGui::Begin("StageView");

	bool isWindowHovered = ImGui::IsWindowHovered();
	if (isWindowHovered)
		processInput();

	ImVec2 size = ImGui::GetContentRegionAvail();
	ImGui::Text((std::to_string(size.x) + " " + std::to_string(size.y)).c_str());

	ImGui::End();
}

void StagePanel::processInput()
{
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		m_eventQueue.emplace(EventType::ON_MOUSE_PRESS, EventButton(ImGuiMouseButton_Right));
		//ImGui::GetMainViewport()
	}
}