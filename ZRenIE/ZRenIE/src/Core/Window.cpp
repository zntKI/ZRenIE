#include "Window.hpp"

#include <iostream>

Window::Window()
	: m_Window(nullptr)
{
}

Window::~Window()
{
	Destroy();
}

bool Window::Initialize(const WindowConfig& windowConfig)
{
	if (!glfwInitialize(windowConfig)) return false;
	if (!gladInitialize()) return false;
}

void Window::Destroy()
{
	if (m_Window)
	{
		glfwDestroyWindow(m_Window);
		m_Window = nullptr;
	}
	glfwTerminate();
}

bool Window::ShouldClose() const
{
	return m_Window ? glfwWindowShouldClose(m_Window) : 1;
}

void Window::SwapBuffers()
{
	if (m_Window)
		glfwSwapBuffers(m_Window);
}

bool Window::glfwInitialize(const WindowConfig& windowConfig)
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
bool Window::gladInitialize()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Error: Failed to initialize GLAD. Terminating program.\n";
		return false;
	}

	return true;
}

void Window::error_callback(int error, const char* descr)
{
	std::cout << "Error: " << descr << "\n";
}