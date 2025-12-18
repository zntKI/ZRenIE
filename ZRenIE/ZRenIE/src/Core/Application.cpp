#include "Application.hpp"
#include "../Utility/Utils.hpp"

#include "Events/Observer.hpp"

#include "Platform.hpp"

#include <iostream>

// TODO: Implement logging system


int Application::s_ScreenWidth = 0;
int Application::s_ScreenHeight = 0;

int Application::GetScreenWidth()
{
	return s_ScreenWidth;
}

int Application::GetScreenHeight()
{
	return s_ScreenHeight;
}

Application::Application(float target_update_rate)
	: TARGET_UPDATE_RATE(target_update_rate), m_Window(std::make_shared<Window>())
{
}

Application::~Application()
{
}

bool Application::Initialize(const WindowConfig& windowConfig)
{
	// Initialize FileSystem here? (if implemented)
	if (!m_Window->Initialize(windowConfig)) return false;

	s_ScreenWidth = windowConfig.WINDOW_WIDTH;
	s_ScreenHeight = windowConfig.WINDOW_HEIGHT;

	m_InputManager.SetCallbacks(m_Window->GetWindowPtr());

	m_UIContext.InitUIContext(m_Window);

	m_Stage = std::make_unique<Stage>();

	PostInitialize();

	return true;
}

bool Application::PostInitialize()
{
	m_InputManager.AddObserver(std::dynamic_pointer_cast<Observer>(m_Window));
	m_InputManager.AddObserver(std::dynamic_pointer_cast<Observer>(m_Stage->GetCameraPtr()));

	m_UIContext.AddObserverToStagePanel(std::dynamic_pointer_cast<Observer>(m_Stage->GetRendererPtr()));
	m_UIContext.AddObserverToStagePanel(std::dynamic_pointer_cast<Observer>(m_Stage->GetCameraPtr()));

	return true;
}

void Application::Run()
{
	float currentFrame = static_cast<float>(glfwGetTime());
	float lag = 0.0f;

	while (!m_Window->ShouldClose())
	{
		currentFrame = static_cast<float>(glfwGetTime());
		m_DeltaTime = currentFrame - m_LastFrame;
		m_LastFrame = currentFrame;
		lag += m_DeltaTime;

		// poll events
		glfwPollEvents();

		// update
		if (lag >= TARGET_UPDATE_RATE)
		{
			// TODO: delegate input events queue to World?
			m_InputManager.ProcessInput();
			m_UIContext.ProcessInput();

			update();
			lag -= TARGET_UPDATE_RATE;
		}

		// render
		render(/*lag / TARGET_UPDATE_RATE*/);
		m_Window->SwapBuffers();
	}
}

void Application::update()
{
	// Empty the event queue from the InputHandler
	m_Stage->Update();
}

void Application::render()
{
	m_UIContext.PreRenderUI();

	m_UIContext.RenderStagePanel(m_Stage->GetRenderResultTexId());
	m_UIContext.RenderHierarchyPanel();

	//ImGui::ShowDemoWindow();

	// TODO: Use stateProgress by asking the World to interpolate between states
	m_Stage->Render();

	m_UIContext.PostRenderUI();
}