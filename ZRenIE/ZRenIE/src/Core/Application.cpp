#include "Application.hpp"
#include "../Utility/Utils.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// TODO: Implement logging system

Application::Application(float target_update_rate)
	: TARGET_UPDATE_RATE(target_update_rate), m_Stage(nullptr)
{
}

Application::~Application()
{
}

bool Application::Initialize(const WindowConfig& windowConfig)
{
	// Initialize FileSystem here? (if implemented)

	if (!m_Window.Initialize(windowConfig)) return false;
	m_Stage = new Stage();

	return true;
}

void Application::Run()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	float lag = 0.0f;

	while (!m_Window.ShouldClose())
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
		render(/*lag / TARGET_UPDATE_RATE*/);
		m_Window.SwapBuffers();
	}
}

void Application::update()
{
	// Empty the event queue from the InputHandler
	m_Stage->Update();
}

void Application::render()
{
	// TODO: Use stateProgress by asking the World to interpolate between states

	m_Stage->Render();
}