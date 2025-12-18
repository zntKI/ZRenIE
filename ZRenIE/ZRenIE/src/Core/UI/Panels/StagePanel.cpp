#include "StagePanel.hpp"

#include "../../Renderer.hpp"

#include "../../../Utility/Utils.hpp"

#include <imgui.h>

#include <tuple>

StagePanel::StagePanel(std::shared_ptr<Window> GLFWWindow)
	: m_GLFWWindow(GLFWWindow)
{
}

void StagePanel::ProcessInput()
{
	for (EventButton button : m_ButtonState)
	{
		Event event(EventType::ON_KEY_REPEAT, button);
		m_eventQueue.push(event);
	}

	emptyQueue();
}

void StagePanel::Render(unsigned int renderResultTexId)
{
	ImGui::Begin("StageView");

	ImVec2 currentWindowSize = ImGui::GetContentRegionAvail();
	if (renderResultTexId != 0)
		ImGui::Image((ImTextureID)(intptr_t)renderResultTexId, currentWindowSize, ImVec2(0, 1), ImVec2(1, 0));

	bool isWindowHovered = ImGui::IsWindowHovered();
	if (isWindowHovered
		|| (!isWindowHovered && shouldStillCheckInput))
		checkForInput();

	checkWindowResize(currentWindowSize);

	ImGui::End();
}

void StagePanel::checkForInput()
{
	// Mouse
	if (ImGui::IsMouseClicked(ImGuiMouseButton_Right))
	{
		m_eventQueue.emplace(EventType::ON_MOUSE_PRESS, EventButton(ImGuiMouseButton_::ImGuiMouseButton_Right),
			std::make_tuple(-1.f, -1.f), m_GLFWWindow->GetWindowPtr());
		shouldStillCheckInput = true;
	}
	if (ImGui::IsMouseDragging(ImGuiMouseButton_Right))
	{
		ImVec2 mouseDragDelta = ImGui::GetMouseDragDelta(ImGuiMouseButton_Right);
		m_eventQueue.emplace(EventType::ON_MOUSE_DRAG, EventButton(EventButton::NONE),
			std::make_tuple(mouseDragDelta.x, mouseDragDelta.y));
	}
	if (ImGui::IsMouseReleased(ImGuiMouseButton_Right))
	{
		m_eventQueue.emplace(EventType::ON_MOUSE_RELEASE, EventButton(ImGuiMouseButton_::ImGuiMouseButton_Right),
			std::make_tuple(-1.f, -1.f), m_GLFWWindow->GetWindowPtr());
		shouldStillCheckInput = false;
	}
	// Keys
	checkKeyInput(ImGuiKey::ImGuiKey_W);
	checkKeyInput(ImGuiKey::ImGuiKey_S);
	checkKeyInput(ImGuiKey::ImGuiKey_A);
	checkKeyInput(ImGuiKey::ImGuiKey_D);
	checkKeyInput(ImGuiKey::ImGuiKey_E);
	checkKeyInput(ImGuiKey::ImGuiKey_Q);
	checkKeyInput(ImGuiKey::ImGuiKey_LeftShift);
}

void StagePanel::checkKeyInput(ImGuiKey keyCode)
{
	EventButton eb(keyCode);
	if (ImGui::IsKeyPressed(keyCode))
	{
		m_ButtonState.insert(eb);
		m_eventQueue.emplace(EventType::ON_KEY_PRESS, EventButton(keyCode));
	}
	if (ImGui::IsKeyReleased(keyCode))
	{
		m_ButtonState.erase(eb);
		m_eventQueue.emplace(EventType::ON_KEY_RELEASE, EventButton(keyCode));
	}
}

void StagePanel::checkWindowResize(ImVec2 currentWindowSize)
{
	if (currentWindowSize.x != previousWindowSize.x
		|| currentWindowSize.y != previousWindowSize.y)
	{
		m_eventQueue.emplace(EventType::ON_WINDOW_RESIZE, EventButton(EventButton::NONE), std::make_tuple(currentWindowSize.x, currentWindowSize.y));
		previousWindowSize = currentWindowSize;
		emptyQueue();
	}
}