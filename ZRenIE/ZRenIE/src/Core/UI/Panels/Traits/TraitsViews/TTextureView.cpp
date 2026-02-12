#include "TTextureView.hpp"

TTextureView::TTextureView()
{
	m_FileDialog.SetTitle("Open Texture");
	m_FileDialog.SetTypeFilters({ ".png", ".jpg" });
}

bool TTextureView::Render(unsigned int currentTextureId, std::string& currentTextureDirectory)
{
	if (ImGui::CollapsingHeader("Texture", ImGuiTreeNodeFlags_DefaultOpen))
	{
		if (ImGui::Button("Open..."))
		{
			m_FileDialog.Open();
		}
		ImGui::SameLine(0, 5.f);
		ImGui::Image((ImTextureID)(intptr_t)currentTextureId, ImVec2(ImGui::GetContentRegionAvail().x * 0.8f, ImGui::GetContentRegionAvail().x * 0.8f), ImVec2(0, 1), ImVec2(1, 0));
	}

	m_FileDialog.Display();
	if (m_FileDialog.HasSelected())
	{
		currentTextureDirectory = m_FileDialog.GetSelected().generic_string();

		m_FileDialog.ClearSelected();

		return true;
	} 

	return false;
}