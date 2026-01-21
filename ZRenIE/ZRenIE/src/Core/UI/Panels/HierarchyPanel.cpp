#include "HierarchyPanel.hpp"

#include <imgui.h>

std::weak_ptr<Character> HierarchyPanel::Render()
{
	ImGui::Begin("Characters");

	checkForInput();

	ImGuiTreeNodeFlags rootFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
	if (!m_SelectedCharacter.expired() && m_SelectedCharacter.lock() == m_World)
		rootFlags |= ImGuiTreeNodeFlags_Selected;

	bool isTreeOpen = ImGui::TreeNodeEx(m_World->m_Name.c_str(), rootFlags);

	if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && !ImGui::IsItemToggledOpen())
		m_SelectedCharacter = m_World;

	if (ImGui::BeginDragDropTarget())
	{
		if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Hierarchy_Character"))
		{
			std::string movedCharID = *(std::string*)(payload->Data);
			m_World->AdjustHierarchy(m_World->GetIdCopy(), movedCharID);
		}
		ImGui::EndDragDropTarget();
	}

	if (isTreeOpen)
	{
		DisplayChildren(m_World->m_Children);
		ImGui::TreePop();
	}

	ImGui::End();

	return m_SelectedCharacter;
}

void HierarchyPanel::DisplayChildren(const std::map<std::string, std::shared_ptr<Character>>& children)
{
	ImGui::Indent(5.f);
	for (auto& child : children)
	{
		ImGuiTreeNodeFlags rootFlags = ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick;
		if (!m_SelectedCharacter.expired() && m_SelectedCharacter.lock() == child.second)
			rootFlags |= ImGuiTreeNodeFlags_Selected;

		bool isTreeOpen = ImGui::TreeNodeEx(child.second->m_Name.c_str(), rootFlags);

		if (ImGui::IsItemClicked(ImGuiMouseButton_Left) && !ImGui::IsItemToggledOpen())
			m_SelectedCharacter = child.second;

		if (ImGui::BeginDragDropSource())
		{
			ImGui::SetDragDropPayload("Hierarchy_Character", &(child.second->GetId()), sizeof(child.second->GetId()));
			ImGui::EndDragDropSource();
		}
		if (ImGui::BeginDragDropTarget())
		{
			if (const ImGuiPayload* payload = ImGui::AcceptDragDropPayload("Hierarchy_Character"))
			{
				std::string movedCharID = *(std::string*)(payload->Data);
				m_World->AdjustHierarchy(child.second->GetIdCopy(), movedCharID);
			}
			ImGui::EndDragDropTarget();
		}

		if (isTreeOpen)
		{
			DisplayChildren(child.second->m_Children);
			ImGui::TreePop();
		}
	}
}

void HierarchyPanel::AssignWorldPtr(std::shared_ptr<World> worldPtr)
{
	m_World = worldPtr;
}

void HierarchyPanel::checkForInput()
{
}