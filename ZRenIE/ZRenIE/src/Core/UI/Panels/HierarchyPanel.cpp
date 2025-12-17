#include "HierarchyPanel.hpp"

#include <imgui.h>

void HierarchyPanel::render()
{
	ImGui::Begin("Characters");

	processInput();

	// Example content
	ImGui::Text("Root");
	ImGui::Indent();
	ImGui::Text("Cube");
	ImGui::Unindent();

	ImGui::End();
}

void HierarchyPanel::processInput()
{
}
