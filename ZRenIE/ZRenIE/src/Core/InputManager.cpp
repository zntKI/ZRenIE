#include "InputManager.hpp"

#include "Platform.hpp"

#include "../Utility/Utils.hpp"

#include <imgui.h>

#include <cassert>

InputManager* InputManager::instance = nullptr;

std::set<EventButton> InputManager::s_buttonState;

bool InputManager::firstMouse = true;
float InputManager::lastX;
float InputManager::lastY;

InputManager::InputManager()
{
	assert(!instance);
	instance = this; // from this
}

InputManager::~InputManager()
{
	instance = nullptr;
}

void InputManager::SetCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);

	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseBtnCallback);
}

void InputManager::AddObserver(std::shared_ptr<Observer> observer)
{
	instance->m_Observers.push_back(observer);
}

void InputManager::ProcessInput()
{
	for (EventButton button : s_buttonState)
	{
		Event event(EventType::ON_KEY_REPEAT, button);
		m_eventQueue.push(event);
	}

	emptyQueue();
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key < 0 || key > GLFW_KEY_LAST
		|| ImGui::GetIO().WantCaptureKeyboard)
		return;

	EventButton eb(key);
	switch (action)
	{
	case GLFW_PRESS:
		s_buttonState.insert(eb);
		instance->m_eventQueue.emplace(EventType::ON_KEY_PRESS, eb);
		break;
	case GLFW_RELEASE:
		s_buttonState.erase(eb);
		instance->m_eventQueue.emplace(EventType::ON_KEY_RELEASE, eb);
		break;
	default:
		return;
	}
}

void InputManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	if (ImGui::GetIO().WantCaptureMouse)
		return;

	Event event(EventType::ON_MOUSE_MOVE, EventButton(GLFW_KEY_UNKNOWN),
		std::make_tuple(static_cast<float>(xpos), static_cast<float>(ypos)));

	instance->m_eventQueue.push(event);
}

void InputManager::mouseBtnCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST
		|| ImGui::GetIO().WantCaptureMouse)
		return;

	EventButton eb(button);
	switch (action)
	{
	case GLFW_PRESS:
		s_buttonState.insert(eb);
		instance->m_eventQueue.emplace(EventType::ON_MOUSE_PRESS, eb, std::make_tuple(-1.f, -1.f), window);
		break;
	case GLFW_RELEASE:
		s_buttonState.erase(eb);
		instance->m_eventQueue.emplace(EventType::ON_MOUSE_RELEASE, eb, std::make_tuple(-1.f, -1.f), window);
		break;
	default:
		return;
	}
}