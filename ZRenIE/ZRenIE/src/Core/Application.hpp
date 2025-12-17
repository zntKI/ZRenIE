#pragma once

#include "Window.hpp"
#include "WindowConfig.hpp"

#include "InputManager.hpp"

#include "Stage.hpp"
#include "Renderer.hpp"
#include "UI/UIContext.hpp"

#include <memory>
#include <vector>

/**
 * @brief The main application class.
 *
 * This class manages the application lifecycle, including initialization,
 * running the main loop, and cleanup. It also handles window creation
 * and rendering.
 */
class Application
{
public:
	static int GetScreenWidth();
	static int GetScreenHeight();

public:
	/**
	 * @brief Constructor for the Application class.
	 *
	 * @param target_update_rate The target update rate in seconds.
	 *		Defaults to 1/60th of a second (60 updates per second).
	 */
	Application(float target_update_rate = 1.f / 60.f);
	/**
	 * @brief Destructor for the Application class.
	 */
	~Application();

	/**
	 * @brief Initializes the application.
	 *
	 * This function initializes GLFW, creates a window, and initializes GLAD.
	 *
	 * @param windowConfig Configuration struct for the window.
	 * @return True if initialization was successful, false otherwise.
	 */
	bool Initialize(const WindowConfig& windowConfig);
	bool PostInitialize();

	/**
	 * @brief Runs the main application loop.
	 *
	 * This function executes the main application loop, which handles
	 * updating and rendering the game.
	 */
	void Run();

private:
	/**
	 * @brief Updates the game state.
	 *
	 * This function updates the game state based on user input and game logic.
	 */
	void update();
	/**
	 * @brief Renders the game.
	 *
	 * This function renders the game to the screen.
	 *
	 * @param stateProgress Interpolation value between the previous and current state.
	 */
	void render();

private:
	// FileSystem m_FileSystem; // TODO: implement FileSystem class?

	std::shared_ptr<Window> m_Window;

	UIContext m_UIContext;

	InputManager m_InputManager;

	std::unique_ptr<Stage> m_Stage;

	const float TARGET_UPDATE_RATE = 1.f / 60.f; // 60 updates per second

	float m_DeltaTime = 0.f;
	float m_LastFrame = 0.f;

	static int s_ScreenWidth;
	static int s_ScreenHeight;
};