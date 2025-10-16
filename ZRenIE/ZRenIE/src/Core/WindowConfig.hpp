#pragma once

// TODO: Move all startup setting into config file?
struct WindowConfig
{
	const int glfw_CONTEXT_VERSION_MAJOR;
	const int glfw_CONTEXT_VERSION_MINOR;

	const int WINDOW_WIDTH;
	const int WINDOW_HEIGHT;

	WindowConfig(int window_width, int window_height,
		   int glfw_context_version_major = 3, int glfw_context_version_minor = 3)
		: WINDOW_WIDTH(window_width),
		  WINDOW_HEIGHT(window_height),
		  glfw_CONTEXT_VERSION_MAJOR(glfw_context_version_major),
		  glfw_CONTEXT_VERSION_MINOR(glfw_context_version_minor)
	{
	}
};