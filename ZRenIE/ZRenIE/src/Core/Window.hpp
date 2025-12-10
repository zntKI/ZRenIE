#pragma once

#include "WindowConfig.hpp"

#include "../Utility/Observer.hpp"

#include "Platform.hpp"

#include <memory>

class Window :public Observer
{
private:
	GLFWwindow* m_Window;

public:
	Window();
	~Window();

	GLFWwindow* GetWindowPtr() const;

	bool Initialize(const WindowConfig& windowConfig);/*Should be Window data loaded from JSON file*/
	void Destroy();

	bool ShouldClose() const;
	void SwapBuffers();

	void OnNotify(Event event) override;

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