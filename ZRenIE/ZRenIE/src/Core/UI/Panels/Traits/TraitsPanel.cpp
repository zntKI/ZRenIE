#include "TraitsPanel.hpp"

#include <imgui.h>

void TraitsPanel::Render(std::weak_ptr<Character> charForRenderTraits)
{
	ImGui::Begin("Traits");

	//checkForInput();

	if (auto character = charForRenderTraits.lock())
	{
        ImGui::Text(character->m_Name.c_str());

		if (ImGui::CollapsingHeader("Transform", ImGuiTreeNodeFlags_DefaultOpen))
		{
            character->m_TransformTrait->Render();
		}
		for (auto& trait : character->m_Traits)
		{
			trait->Render();
		}
	}

	ImGui::End();
}

void TraitsPanel::checkForInput()
{
}