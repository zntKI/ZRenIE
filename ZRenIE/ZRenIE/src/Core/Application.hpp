#pragma once

#include "WindowConfig.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Application
{
public:
	Application(float target_update_rate = 1.f / 60.f);
	~Application();

	bool Initialize(const WindowConfig& windowConfig);
	void Run();

private:
	void update();
	void render(float stateProgress);

private: // member variables // TODO: make use of smart pointers?
	GLFWwindow* m_Window; // TODO: move to Window wrapper class?

	// World* m_World; // TODO: implement World class? Handles all game objects
	// Renderer* m_Renderer; // TODO: implement Renderer class? Handles all rendering

	const float TARGET_UPDATE_RATE = 1.f / 60.f; // 60 updates per second

	float m_DeltaTime;
	float m_LastFrame;

private:
	bool glfwInitialize(const WindowConfig& windowConfig);
	bool gladInitialize();

private: // helper functions TODO: move to Utility?
	static void error_callback(int error, const char* descr);
	//static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};