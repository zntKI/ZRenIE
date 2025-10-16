#pragma once

#include "WindowConfig.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

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
	void render(float stateProgress);

private: // member variables // TODO: make use of smart pointers?
	GLFWwindow* m_Window; // TODO: move to Window wrapper class?

	// World* m_World; // TODO: implement World class? Handles all game objects
	// Renderer* m_Renderer; // TODO: implement Renderer class? Handles all rendering

	const float TARGET_UPDATE_RATE = 1.f / 60.f; // 60 updates per second

	float m_DeltaTime;
	float m_LastFrame;

private:
	/**
	 * @brief Initializes GLFW.
	 *
	 * This helper function initializes the GLFW library.
	 *
	 * @param windowConfig Configuration struct for the window.
	 * @return True if initialization was successful, false otherwise.
	 */
	bool glfwInitialize(const WindowConfig& windowConfig);
	/**
	 * @brief Initializes GLAD.
	 *
	 * This helper function initializes the GLAD library.
	 *
	 * @return True if initialization was successful, false otherwise.
	 */
	bool gladInitialize();

private: // helper functions TODO: move to Utility?
	/**
	 * @brief Error callback function for GLFW.
	 *
	 * This function is called when a GLFW error occurs.
	 *
	 * @param error The error code.
	 * @param descr A description of the error.
	 */
	static void error_callback(int error, const char* descr);
	//static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

};