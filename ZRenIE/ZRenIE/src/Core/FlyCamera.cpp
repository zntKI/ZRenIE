#include "FlyCamera.hpp"

#include "Application.hpp"
#include "../Utility/Utils.hpp"

FlyCamera::FlyCamera(glm::vec3 position, glm::vec3 up, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MovementSpeedFast(SPEED_FAST), m_CurrentMovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM),
	m_LastX(Application::GetScreenWidth() / 2.f), m_LastY(Application::GetScreenHeight() / 2.f)
{
	Position = position;
	WorldUp = up;
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

FlyCamera::FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch)
	: Front(glm::vec3(0.0f, 0.0f, -1.0f)), MovementSpeed(SPEED), MovementSpeedFast(SPEED_FAST), m_CurrentMovementSpeed(SPEED), MouseSensitivity(SENSITIVITY), Zoom(ZOOM),
	m_LastX(Application::GetScreenWidth() / 2.f), m_LastY(Application::GetScreenHeight() / 2.f)
{
	Position = glm::vec3(posX, posY, posZ);
	WorldUp = glm::vec3(upX, upY, upZ);
	Yaw = yaw;
	Pitch = pitch;
	updateCameraVectors();
}

glm::mat4 FlyCamera::GetViewMatrix() const
{
	return glm::lookAt(Position, Position + Front, Up);
}

void FlyCamera::OnNotify(Event event)
{
	if (m_CameraInputMode != CameraIputMode::TRAVERSER)
	{
		if (event.eventType == EventType::ON_MOUSE_PRESS)
			processMouseBtnPress(event.eventData);

		return;
	}

	switch (event.eventType)
	{
		// Key
	case EventType::ON_KEY_PRESS:
		processKeyboardPress(event.eventData);
		break;
	case EventType::ON_KEY_REPEAT:
		processKeyboardRepeat(event.eventData);
		break;
	case EventType::ON_KEY_RELEASE:
		processKeyboardRelease(event.eventData);
		break;
		// Mouse
	case EventType::ON_MOUSE_MOVE:
		processMouseMovement(event.eventData);
		break;
	case EventType::ON_MOUSE_PRESS:
		processMouseBtnPress(event.eventData);
		break;
	case EventType::ON_MOUSE_REPEAT:
		processMouseBtnRepeat(event.eventData);
		break;
	case EventType::ON_MOUSE_RELEASE:
		processMouseBtnRelease(event.eventData);
		break;
	default:
		break;
	}
}

void FlyCamera::processKeyboardPress(EventData eventData)
{
	if (eventData.key == MOVE_FAST)
		m_CurrentMovementSpeed = MovementSpeedFast;
}

void FlyCamera::processKeyboardRepeat(EventData eventData)
{
	int keyCode = eventData.key;

	if (keyCode == FORWARD)
		Position += Front * m_CurrentMovementSpeed;
	if (keyCode == BACKWARD)
		Position -= Front * m_CurrentMovementSpeed;
	if (keyCode == LEFT)
		Position -= Right * m_CurrentMovementSpeed;
	if (keyCode == RIGHT)
		Position += Right * m_CurrentMovementSpeed;
	if (keyCode == UP)
		Position += Up * m_CurrentMovementSpeed;
	if (keyCode == DOWN)
		Position -= Up * m_CurrentMovementSpeed;
}

void FlyCamera::processKeyboardRelease(EventData eventData)
{
	if (eventData.key == MOVE_FAST)
		m_CurrentMovementSpeed = MovementSpeed;
}

void FlyCamera::processMouseMovement(EventData eventData)
{
	float xpos = get<0>(eventData.mousePos);
	float ypos = get<1>(eventData.mousePos);

	if (m_FirstMouse) // initially set to true
	{
		m_LastX = xpos;
		m_LastY = ypos;
		m_FirstMouse = false;
	}

	float xoffset = xpos - m_LastX;
	float yoffset = m_LastY - ypos; // reversed
	m_LastX = xpos;
	m_LastY = ypos;


	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (Pitch > 89.0f)
		Pitch = 89.0f;
	if (Pitch < -89.0f)
		Pitch = -89.0f;

	// update Front, Right and Up Vectors using the updated Euler angles
	updateCameraVectors();
}

void FlyCamera::processMouseBtnPress(EventData eventData)
{
	if (eventData.mouseBtn == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_CameraInputMode = CameraIputMode::TRAVERSER;
		m_FirstMouse = true;

		if (eventData.window)
		{
			glfwSetInputMode(eventData.window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		}
	}
}

void FlyCamera::processMouseBtnRepeat(EventData eventData)
{
}

void FlyCamera::processMouseBtnRelease(EventData eventData)
{
	if (eventData.mouseBtn == GLFW_MOUSE_BUTTON_RIGHT)
	{
		m_CameraInputMode = CameraIputMode::OBSERVER;

		if (eventData.window)
		{
			glfwSetInputMode(eventData.window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		}
	}
}

void FlyCamera::updateCameraVectors()
{
	// calculate the new Front vector
	glm::vec3 front;
	front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	front.y = sin(glm::radians(Pitch));
	front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
	Front = glm::normalize(front);
	// also re-calculate the Right and Up vector
	Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
	Up = glm::normalize(glm::cross(Right, Front));
}