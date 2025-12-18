#pragma once

#include "Panel.hpp"

#include "../../Events/Sender.hpp"

#include "../../Window.hpp"

#include <memory>
#include <set>

class StagePanel : public Panel, public Sender
{
private:
	std::shared_ptr<Window> m_GLFWWindow;

	ImVec2 previousWindowSize{0.f, 0.f};

	std::set<EventButton> m_ButtonState;

	// To enable camera rotation through mouse movement even if mouse is outside of the window's bounds
	bool shouldStillCheckInput = false;

public:
	StagePanel(std::shared_ptr<Window> GLFWWindow);

	void Render(unsigned int renderResultTexId);

	void ProcessInput();

protected:
	void checkForInput() override;

private:
	void checkKeyInput(ImGuiKey keyCode);

	void checkWindowResize(ImVec2 currentWindowSize);
};