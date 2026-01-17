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

GLFWwindow* Window::GetWindowPtr() const
{
	return m_Window;
}

bool Window::Initialize(const nlohmann::json& windowConfigData)
{
	if (!glfwInitialize(windowConfigData)) return false;
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

void Window::OnNotify(Event event)
{
	if (event.eventType == EventType::ON_KEY_PRESS && event.eventData.button == EventButton::KEY_ESCAPE)
	{
		glfwSetWindowShouldClose(m_Window, true);
	}
}

bool Window::glfwInitialize(const nlohmann::json& windowConfigData)
{
	glfwSetErrorCallback(error_callback);

	if (!glfwInit())
		return false;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, windowConfigData["glfwContextVersionMajor"]);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, windowConfigData["glfwContextVersionMinor"]);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	m_Window = glfwCreateWindow(windowConfigData["windowWidth"],
		windowConfigData["windowHeight"], "Window", NULL, NULL);
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