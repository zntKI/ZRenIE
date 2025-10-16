#include "Application.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// TODO: Implement logging system

Application::Application(float target_update_rate)
	: TARGET_UPDATE_RATE(target_update_rate), m_Window(nullptr)
{
}

Application::~Application()
{
	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	glfwTerminate();
}

bool Application::Initialize(const WindowConfig& windowConfig)
{
	if (!glfwInitialize(windowConfig)) return false;
	if (!gladInitialize()) return false;

	return true;
}

void Application::Run()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	float lag = 0.0f;

	while (!glfwWindowShouldClose(m_Window))
	{
		currentFrame = static_cast<float>(glfwGetTime());
		m_DeltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;
		lag += m_DeltaTime;
		
		// poll events
		glfwPollEvents();
		// process input
		// TODO:
		//		handle input callbacks into the input manager
		//		store input events in a queue inside input manager
		//		at the beginning of each update, delegate the input queue to the update manager (World?)

		// update
		if (lag >= TARGET_UPDATE_RATE)
		{
			// TODO: delegate input events queue to World?

			update();
			lag -= TARGET_UPDATE_RATE;
		}

		// render
		render(lag / TARGET_UPDATE_RATE);
		glfwSwapBuffers(m_Window);
	}
}

void Application::update()
{
}

void Application::render(float stateProgress)
{
	// TODO: Use stateProgress by asking the World to interpolate between states

	// TODO: Move this into the Renderer class:
	glClearColor(0.f, 64.f, 128.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

bool Application::glfwInitialize(const WindowConfig& windowConfig)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowConfig.glfw_CONTEXT_VERSION_MAJOR);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowConfig.glfw_CONTEXT_VERSION_MINOR);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(windowConfig.WINDOW_WIDTH, windowConfig.WINDOW_HEIGHT, "Window", NULL, NULL);
	if (!m_Window)
	{
		std::cout << "Error: Window creation failed. Terminating program.\n";
		return false;
	}
	glfwMakeContextCurrent(m_Window);

	return true;
}
bool Application::gladInitialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Failed to initialize GLAD. Terminating program.\n";
		return false;
	}

	return true;
}

void Application::error_callback(int error, const char* descr)
{
	std::cout << "Error: " << descr << "\n";
}