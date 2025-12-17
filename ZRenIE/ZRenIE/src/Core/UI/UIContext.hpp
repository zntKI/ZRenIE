#pragma once

#include "Panels/StagePanel.hpp"
#include "Panels/HierarchyPanel.hpp"

#include "../Renderer.hpp"

#include "../Platform.hpp"

class UIContext
{
private:
	static bool s_isInstantiated;

	StagePanel m_StagePanel;
	HierarchyPanel m_HierarchyPanel;

public:
	UIContext();
	/// <summary>
	/// Lazy init ImGui
	/// </summary>
	void InitImGui(GLFWwindow* window);
	~UIContext();

	void PreRenderUI();

	void RenderStagePanel();
	void RenderHierarchyPanel();

	void PostRenderUI();
};