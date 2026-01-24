#include "TModelView.hpp"

#include <algorithm>

TModelView::TModelView()
{
    m_FileDialog.SetTitle("Open Model");
    m_FileDialog.SetTypeFilters({ ".fbx", ".obj" });
}

bool TModelView::Render(std::string& currentModelName, std::string& currentModelDirectory)
{
	/*if (ImGui::CollapsingHeader("Model", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Open..."))
		{
			m_FileDialog.Open();
		}
		ImGui::SameLine(0, 5.f);
		ImGui::Text(currentModelName.c_str());
	}

	m_FileDialog.Display();
	if (m_FileDialog.HasSelected())
	{
		currentModelDirectory = m_FileDialog.GetSelected().generic_string();
		currentModelName = currentModelDirectory.substr(currentModelDirectory.find_last_of('/') + 1);

		m_FileDialog.ClearSelected();

		return true;
	}*/

	return false;
}