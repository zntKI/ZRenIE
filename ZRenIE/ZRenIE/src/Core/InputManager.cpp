#include "InputManager.hpp"

#include "Platform.hpp"

#include "../Utility/Utils.hpp"

#include <cassert>

InputManager* InputManager::instance = nullptr;

std::set<int> InputManager::s_keyState;
std::set<int> InputManager::s_mouseBtnState;

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
}

void InputManager::SetCallbacks(GLFWwindow* window)
{
	glfwSetKeyCallback(window, keyCallback);

	glfwSetCursorPosCallback(window, mousePosCallback);
	glfwSetMouseButtonCallback(window, mouseBtnCallback);
}

void InputManager::ProcessInput()
{
	for (int key : s_keyState)
	{
		Event event(EventType::ON_KEY_REPEAT, key);
		s_eventQueue.push(event);
	}

	for (int button : s_mouseBtnState)
	{
		Event event(EventType::ON_MOUSE_REPEAT, -1, std::make_tuple(-1.f, -1.f), button);
		s_eventQueue.push(event);
	}

	emptyQueue();
}

void InputManager::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (key < 0 || key > GLFW_KEY_LAST)
		return;

	Event event;
	switch (action)
	{
	case GLFW_PRESS:
		s_keyState.insert(key);
		event = Event(EventType::ON_KEY_PRESS, key);
		break;
	case GLFW_RELEASE:
		s_keyState.erase(key);
		event = Event(EventType::ON_KEY_RELEASE, key);
		break;
	default:
		return;
	}

	instance->s_eventQueue.push(event);
}

void InputManager::mousePosCallback(GLFWwindow* window, double xpos, double ypos)
{
	Event event(EventType::ON_MOUSE_MOVE, -1,
		std::make_tuple(static_cast<float>(xpos), static_cast<float>(ypos)));

	instance->s_eventQueue.push(event);
}

void InputManager::mouseBtnCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (button < 0 || button > GLFW_MOUSE_BUTTON_LAST)
		return;

	Event event;
	switch (action)
	{
	case GLFW_PRESS:
		s_mouseBtnState.insert(button);
		event = Event(EventType::ON_MOUSE_PRESS, -1, std::make_tuple(-1.f, -1.f), button, window);
		break;
	case GLFW_RELEASE:
		s_mouseBtnState.erase(button);
		event = Event(EventType::ON_MOUSE_RELEASE, -1, std::make_tuple(-1.f, -1.f), button, window);
		break;
	default:
		return;
	}

	instance->s_eventQueue.push(event);
}