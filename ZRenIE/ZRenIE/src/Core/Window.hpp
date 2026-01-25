#pragma once

#include "WindowConfig.hpp"

#include "Events/Observer.hpp"

#include "Platform.hpp"

#include "nlohmann/json.hpp"

#include <memory>

class Window :public Observer
{
private:
	GLFWwindow* m_Window;

public:
	Window();
	~Window();

	GLFWwindow* GetWindowPtr() const;

	bool Initialize(const nlohmann::json& windowConfigData);
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
	 */
	bool glfwInitialize(const nlohmann::json& windowConfigData);
	/**
	 * @brief Initializes GLAD.
	 *
	 * This helper function initializes the GLAD library.
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