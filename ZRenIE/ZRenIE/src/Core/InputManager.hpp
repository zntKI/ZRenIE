#pragma once

#include "../Utility/Observer.hpp"

#include "Platform.hpp"

#include <memory>
#include <vector>
#include <queue>
#include <set>

class InputManager
{
private:
	static bool s_isInstantiated;

	static std::vector<std::shared_ptr<Observer>> m_Observers;

	static std::queue<Event> s_eventQueue;

	static std::set<int> s_keyState;
	static std::set<int> s_mouseBtnState;

	static bool firstMouse;
	static float lastX;
	static float lastY;

public:
	InputManager();
	~InputManager();

	void SetCallbacks(GLFWwindow* window);

	void AddObserver(std::shared_ptr<Observer> observer);
	//void RemoveObserver(std::shared_ptr<Observer> observer);

	void ProcessInput();

private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods);

	void emptyQueue();
};