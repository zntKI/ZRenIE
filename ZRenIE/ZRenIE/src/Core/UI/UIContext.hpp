#pragma once

#include "Panels/StagePanel.hpp"
#include "Panels/HierarchyPanel.hpp"

#include "../Platform.hpp"

#include "../Window.hpp"

class UIContext
{
private:
	static bool s_isInstantiated;

	std::shared_ptr<Window> m_GLFWWindow;

	std::unique_ptr<StagePanel> m_StagePanel;
	HierarchyPanel m_HierarchyPanel;

public:
	UIContext();
	/// <summary>
	/// Lazy init UIContext
	/// </summary>
	void InitUIContext(std::shared_ptr<Window> GLFWWindow);
	~UIContext();

	void PreRenderUI();

	void RenderStagePanel(unsigned int renderResultTexId);
	void RenderHierarchyPanel();

	void PostRenderUI();

	void ProcessInput();

	void AddObserverToStagePanel(std::shared_ptr<Observer> observer);

private:
	/// <summary>
	/// Lazy init ImGui
	/// </summary>
	void initImGui();
};