#pragma once

#include "Events/Sender.hpp"
#include "Events/Observer.hpp"

#include "Platform.hpp"

#include <memory>
#include <vector>
#include <queue>
#include <set>

class InputManager : public Sender
{
private:
	static bool s_isInstantiated;
	static InputManager* instance;

	static std::set<int> s_keyState;
	static std::set<int> s_mouseBtnState;

	static bool firstMouse;
	static float lastX;
	static float lastY;

public:
	InputManager();
	~InputManager();

	/*static InputManager& instance()
	{
		static InputManager instance = InputManager();
		return instance;
	}*/

	void SetCallbacks(GLFWwindow* window);

	void ProcessInput();

private:
	static void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void mousePosCallback(GLFWwindow* window, double xpos, double ypos);
	static void mouseBtnCallback(GLFWwindow* window, int button, int action, int mods);
};