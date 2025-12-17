#pragma once

#include "../Platform.hpp"

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
	ON_MOUSE_PRESS,
	ON_MOUSE_REPEAT,
	ON_MOUSE_RELEASE,
};

struct EventData
{
	EventData(const int key,
		const std::tuple<float, float>& mousePos, const int mouseBtn,
		GLFWwindow* window)
		: key(key), mousePos(mousePos), mouseBtn(mouseBtn), window(window)
	{
	};

	int key;
	std::tuple<float, float> mousePos;
	int mouseBtn;

	GLFWwindow* window;
};

struct Event
{
	Event()
		: eventType(EventType::NONE), eventData(-1, std::make_tuple(-1.f, -1.f), -1, nullptr)
	{
	};
	Event(const EventType eventType, const int key = -1,
		const std::tuple<float, float>& mousePos = std::make_tuple(-1.f, -1.f), const int mouseBtn = -1,
		GLFWwindow* window = nullptr)
		: eventType(eventType), eventData(key, mousePos, mouseBtn, window)
	{
	};

	EventType eventType;
	EventData eventData;
};