#pragma once

#include "../Platform.hpp"

#include <imgui.h>

#include <tuple>

enum class EventType
{
	NONE = 0,
	// Keys
	ON_KEY_PRESS,
	ON_KEY_REPEAT,
	ON_KEY_RELEASE,
	// Mouse
	ON_MOUSE_MOVE,
	ON_MOUSE_DRAG,
	ON_MOUSE_PRESS,
	ON_MOUSE_REPEAT,
	ON_MOUSE_RELEASE,
	// Window
	ON_WINDOW_RESIZE
};

typedef int EventButtonCode;

struct EventButton
{
private:
	EventButtonCode buttonCode;

public:
	explicit EventButton(int buttonCode) // GLFW
	{
		// Parse from GLFW
		this->buttonCode = To_EventButton_From_GLFWButton(buttonCode);
	}

	explicit EventButton(ImGuiKey buttonCode) // ImGui
	{
		// Parse from ImGui
		this->buttonCode = To_EventButton_From_ImGuiButton(buttonCode);
	}

	explicit EventButton(ImGuiMouseButton_ buttonCode) // ImGui
	{
		// Parse from ImGui
		this->buttonCode = To_EventButton_From_ImGuiButton(buttonCode);
	}

	bool operator==(EventButtonCode buttonCode) const noexcept
	{
		return this->buttonCode == buttonCode;
	}

	EventButtonCode Code() const noexcept { return buttonCode; }

	friend bool operator<(const EventButton& a, const EventButton& b) noexcept
	{
		return a.buttonCode < b.buttonCode;
	}

private:
	inline EventButtonCode To_EventButton_From_GLFWButton(int buttonCode)
	{
		switch (buttonCode)
		{
			// Mouse
		case GLFW_MOUSE_BUTTON_LEFT:   return EventButton::MOUSE_LEFT;
		case GLFW_MOUSE_BUTTON_RIGHT:  return EventButton::MOUSE_RIGHT;
		case GLFW_MOUSE_BUTTON_MIDDLE: return EventButton::MOUSE_MIDDLE;
			// Keys
		case GLFW_KEY_W: return EventButton::KEY_W;
		case GLFW_KEY_A: return EventButton::KEY_A;
		case GLFW_KEY_S: return EventButton::KEY_S;
		case GLFW_KEY_D: return EventButton::KEY_D;
		case GLFW_KEY_E: return EventButton::KEY_E;
		case GLFW_KEY_Q: return EventButton::KEY_Q;
		case GLFW_KEY_LEFT_SHIFT: return EventButton::KEY_LEFT_SHIFT;
		case GLFW_KEY_ESCAPE: return EventButton::KEY_ESCAPE;
			//
		case GLFW_KEY_UNKNOWN:
		default:
			return EventButton::UNKNOWN;
		}
	}
	inline EventButtonCode To_EventButton_From_ImGuiButton(int buttonCode)
	{
		switch (buttonCode)
		{
			// Mouse
		case ImGuiMouseButton_Left:   return EventButton::MOUSE_LEFT;
		case ImGuiMouseButton_Right:  return EventButton::MOUSE_RIGHT;
		case ImGuiMouseButton_Middle: return EventButton::MOUSE_MIDDLE;
			// Keys
		case ImGuiKey_W: return EventButton::KEY_W;
		case ImGuiKey_A: return EventButton::KEY_A;
		case ImGuiKey_S: return EventButton::KEY_S;
		case ImGuiKey_D: return EventButton::KEY_D;
		case ImGuiKey_E: return EventButton::KEY_E;
		case ImGuiKey_Q: return EventButton::KEY_Q;
		case ImGuiKey_LeftShift: return EventButton::KEY_LEFT_SHIFT;
			//
		default: return EventButton::UNKNOWN;
		}
	}

public:
	//General
	static EventButtonCode const UNKNOWN = -1;
	static EventButtonCode const NONE = 0;
	// Mouse
	static EventButtonCode const MOUSE_LEFT = 1;
	static EventButtonCode const MOUSE_RIGHT = 2;
	static EventButtonCode const MOUSE_MIDDLE = 3;
	// Keys
	static EventButtonCode const KEY_W = 4;
	static EventButtonCode const KEY_S = 5;
	static EventButtonCode const KEY_A = 6;
	static EventButtonCode const KEY_D = 7;
	static EventButtonCode const KEY_E = 8;
	static EventButtonCode const KEY_Q = 9;
	static EventButtonCode const KEY_LEFT_SHIFT = 10;
	static EventButtonCode const KEY_ESCAPE = 11;
};

struct EventData
{
	EventData(const EventButton button,
		const std::tuple<float, float>& twoValueChange,
		GLFWwindow* window)
		: button(button), twoValueChange(twoValueChange), window(window)
	{
	};

	EventButton button;
	// Could be mouse position change or viewport size change
	std::tuple<float, float> twoValueChange;

	GLFWwindow* window;
};

struct Event
{
	Event(const EventType eventType, const EventButton button,
		const std::tuple<float, float>& twoValueChange = std::make_tuple(-1.f, -1.f),
		GLFWwindow* window = nullptr)
		: eventType(eventType), eventData(button, twoValueChange, window)
	{
	};

	EventType eventType;
	EventData eventData;
};