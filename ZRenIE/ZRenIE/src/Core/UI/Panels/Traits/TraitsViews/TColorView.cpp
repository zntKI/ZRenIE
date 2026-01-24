#include "TColorView.hpp"

#include <imgui.h>

void TColorView::Render(glm::vec3& color)
{
	if (ImGui::CollapsingHeader("Material", ImGuiTreeNodeFlags_DefaultOpen))
	{
		ImGui::ColorPicker3("Color", (float*)&color, ImGuiColorEditFlags_PickerHueWheel | ImGuiColorEditFlags_DisplayRGB);
	}
}