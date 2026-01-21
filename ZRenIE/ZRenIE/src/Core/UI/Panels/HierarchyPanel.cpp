#include "HierarchyPanel.hpp"

#include <imgui.h>

void HierarchyPanel::Render()
{
	ImGui::Begin("Characters");

	checkForInput();

	bool isTreeOpen = ImGui::TreeNodeEx(m_World->m_Name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);

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
}

void HierarchyPanel::DisplayChildren(const std::map<std::string, std::shared_ptr<Character>>& children) const
{
	ImGui::Indent(5.f);
	for (auto& child : children)
	{
		bool isTreeOpen = ImGui::TreeNodeEx(child.second->m_Name.c_str(), ImGuiTreeNodeFlags_OpenOnArrow);

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