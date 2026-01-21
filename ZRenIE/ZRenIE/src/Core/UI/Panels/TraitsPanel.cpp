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
			TransformProperties localTransform = character->m_TransformTrait->GetLocalTransformPropertiesCopy();

            ImGui::PushItemWidth(160.0f);

            // Position
            ImGui::Text("Position");
            ImGui::SameLine(100.0f);
            float pos[3] = { localTransform.Position.x, localTransform.Position.y, localTransform.Position.z };
            bool posChanged = ImGui::DragFloat3("##pos", pos, 0.1f, -FLT_MAX, FLT_MAX, "%.3f");

            // Rotation (degrees)
            ImGui::Text("Rotation");
            ImGui::SameLine(100.0f);
            float rot[3] = { localTransform.Rotation.x, localTransform.Rotation.y, localTransform.Rotation.z };
            bool rotChanged = ImGui::DragFloat3("##rot", rot, 0.5f, -360.0f, 360.0f, "%.2f");

            // Scale
            ImGui::Text("Scale");
            ImGui::SameLine(100.0f);
            float scl[3] = { localTransform.Scale.x, localTransform.Scale.y, localTransform.Scale.z };
            bool sclChanged = ImGui::DragFloat3("##scl", scl, 0.01f, 0.0f, FLT_MAX, "%.3f");

            ImGui::PopItemWidth();

            // Apply changes
            if (posChanged || rotChanged || sclChanged)
            {
                localTransform.Position = { pos[0], pos[1], pos[2] };
                localTransform.Rotation = { rot[0], rot[1], rot[2] }; // stored as degrees
                localTransform.Scale = { scl[0], scl[1], scl[2] };
                character->UpdateLocalTransform(localTransform);
            }
		}
	}

	ImGui::End();
}

void TraitsPanel::checkForInput()
{
}