#pragma once

// TODO: Move all startup setting into config file?

/**
 * @brief Struct for window configuration settings.
 *
 * This struct holds the configuration settings for the application window,
 * such as window dimensions and OpenGL context versions.
 */
struct WindowConfig
{
	/**
	 * @brief The major version of the OpenGL context.
	 */
	const int glfw_CONTEXT_VERSION_MAJOR;
	/**
	 * @brief The minor version of the OpenGL context.
	 */
	const int glfw_CONTEXT_VERSION_MINOR;

	/**
	 * @brief The width of the window in pixels.
	 */
	const int WINDOW_WIDTH;
	/**
	 * @brief The height of the window in pixels.
	 */
	const int WINDOW_HEIGHT;

	/**
	 * @brief Constructor for the WindowConfig struct.
	 *
	 * @param window_width The width of the window in pixels.
	 * @param window_height The height of the window in pixels.
	 * @param glfw_context_version_major The major version of the OpenGL context. Defaults to 3.
	 * @param glfw_context_version_minor The minor version of the OpenGL context. Defaults to 3.
	 */
	WindowConfig(int window_width, int window_height,
		   int glfw_context_version_major = 3, int glfw_context_version_minor = 3)
		: WINDOW_WIDTH(window_width),
		  WINDOW_HEIGHT(window_height),
		  glfw_CONTEXT_VERSION_MAJOR(glfw_context_version_major),
		  glfw_CONTEXT_VERSION_MINOR(glfw_context_version_minor)
	{
	}
};