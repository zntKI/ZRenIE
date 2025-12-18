#include "HierarchyPanel.hpp"

#include <imgui.h>

void HierarchyPanel::Render()
{
	ImGui::Begin("Characters");

	checkForInput();

	// Example content
	ImGui::Text("Root");
	ImGui::Indent();
	ImGui::Text("Cube");
	ImGui::Unindent();

	ImGui::End();
}

void HierarchyPanel::checkForInput()
{
}