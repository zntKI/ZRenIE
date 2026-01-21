#include "Application.hpp"
#include "../Utility/Utils.hpp"

#include "Events/Observer.hpp"

#include "Platform.hpp"

#include <nlohmann/json.hpp>

#include <fstream>
#include <iostream>

// TODO: Implement logging system


unsigned int Application::s_ScreenWidth = 0;
unsigned int Application::s_ScreenHeight = 0;

unsigned int Application::GetScreenWidth()
{
	return s_ScreenWidth;
}

unsigned int Application::GetScreenHeight()
{
	return s_ScreenHeight;
}

Application::Application()
	: m_Window(std::make_shared<Window>())
{
}

Application::~Application()
{
}

void Application::Start(const std::string& configFilePath)
{
	std::ifstream file(configFilePath);
	if (!file.fail())
	{
		nlohmann::json data = nlohmann::json::parse(file);

#pragma region WindowConfig

		nlohmann::json windowConfigData = data["windowConfig"];
		if (!m_Window->Initialize(windowConfigData)) return;

		s_ScreenWidth = windowConfigData["windowWidth"];
		s_ScreenHeight = windowConfigData["windowHeight"];

#pragma endregion

#pragma region ApplicationConfig

		nlohmann::json applicationConfigData = data["applicationConfig"];
		targetUpdateRate = applicationConfigData["gameLoopTargetUpdateRate"];

#pragma endregion

		m_InputManager.SetCallbacks(m_Window->GetWindowPtr());

		m_UIContext.InitUIContext(m_Window);

#pragma region StageConfig

		nlohmann::json stageConfigData = data["stageConfig"];
		m_Stage = std::make_unique<Stage>(
			StageConfig
			{
				stageConfigData["worldConfig"],
				RendererConfig
				{
				/* m_WorldCamera */ nullptr,
				/* shouldRenderToFramebuffer */ stageConfigData["renderConfig"]["shouldRenderToFramebuffer"],
				}
			}
		);

#pragma endregion

		PostInitialize();


		Run();
	}
}

void Application::PostInitialize()
{
	m_InputManager.AddObserver(std::dynamic_pointer_cast<Observer>(m_Window));
	m_InputManager.AddObserver(std::dynamic_pointer_cast<Observer>(m_Stage->GetCameraPtr()));

	m_UIContext.AddObserverToStagePanel(std::dynamic_pointer_cast<Observer>(
		m_Stage->GetRendererPtr()->GetImGuiFramebuffer())
	);
	m_UIContext.AddObserverToStagePanel(std::dynamic_pointer_cast<Observer>(m_Stage->GetCameraPtr()));

	m_UIContext.AssignWorldToHierarchyPanel(m_Stage->GetWorldPtr());
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
		if (lag >= targetUpdateRate)
		{
			// TODO: delegate input events queue to World?
			m_InputManager.ProcessInput();
			m_UIContext.ProcessInput();

			update();
			lag -= targetUpdateRate;
		}

		// render
		render(/*lag / TARGET_UPDATE_RATE*/);
		m_Window->SwapBuffers();
	}
}

void Application::update()
{
	m_Stage->Update();
}

void Application::render()
{
	m_UIContext.PreRenderUI();

	m_UIContext.RenderStagePanel();
	m_UIContext.RenderHierarchyPanel();

	// TODO: Use stateProgress by asking the World to interpolate between states
	m_Stage->Render();

	m_UIContext.PostRenderUI();
}