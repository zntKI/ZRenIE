#pragma once

#include "Panels/StagePanel.hpp"
#include "Panels/HierarchyPanel.hpp"
#include "Panels/TraitsPanel.hpp"

#include "../Platform.hpp"

#include "../Window.hpp"

#include "../World.hpp"

class UIContext
{
private:
	static bool s_isInstantiated;

	std::shared_ptr<Window> m_GLFWWindow;

	std::unique_ptr<StagePanel> m_StagePanel;
	std::unique_ptr<HierarchyPanel> m_HierarchyPanel;
	std::unique_ptr<TraitsPanel> m_TraitsPanel;

public:
	UIContext();
	/// <summary>
	/// Lazy init UIContext
	/// </summary>
	void InitUIContext(std::shared_ptr<Window> GLFWWindow);
	~UIContext();

	void PreRenderUI();

	void RenderUI();

	void PostRenderUI();

	void ProcessInput();

	void AddObserverToStagePanel(std::shared_ptr<Observer> observer);
	void AssignWorldToHierarchyPanel(std::shared_ptr<World> worldPtr);

private:
	/// <summary>
	/// Lazy init ImGui
	/// </summary>
	void initImGui();
};