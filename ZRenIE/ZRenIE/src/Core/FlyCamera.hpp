#pragma once

#include "Events/Observer.hpp"

#include "Platform.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum CameraIputMode
{
	OBSERVER,
	TRAVERSER
};

// Default camera values
const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = .1f;
const float SPEED_FAST = 2.f * SPEED;
const float SENSITIVITY = 0.1f;

const float ZOOM = 45.0f;
const float NEAR_PLANE = .1f;
const float FAR_PLANE = 100.f;


// An abstract camera class that processes input and calculates the corresponding Euler Angles, Vectors and Matrices for use in OpenGL
class FlyCamera : public Observer
{
public:
	// camera Attributes
	glm::vec3 Position;
	glm::vec3 Front;
	glm::vec3 Up;
	glm::vec3 Right;
	glm::vec3 WorldUp;
	// euler Angles
	float Yaw;
	float Pitch;
	// camera options
	float MovementSpeed;
	float MovementSpeedFast;
	float MouseSensitivity;

	float Zoom;
	float NearPlane;
	float FarPlane;

private:
	CameraIputMode m_CameraInputMode = CameraIputMode::OBSERVER;

	float m_CurrentMovementSpeed;

	bool m_FirstMouse = true;
	float m_LastX, m_LastY;

	bool m_IsRightMouseBtnPressed = false;

public:

	// constructor with vectors
	FlyCamera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), float yaw = YAW, float pitch = PITCH);
	// constructor with scalar values
	FlyCamera(float posX, float posY, float posZ, float upX, float upY, float upZ, float yaw, float pitch);

	// returns the view matrix calculated using Euler Angles and the LookAt Matrix
	glm::mat4 GetViewMatrix() const;
	glm::mat4 GetProjMatrix(float aspectRatio) const;

	void OnNotify(Event event) override;

private:
	void processKeyboardPress(EventData eventData);
	void processKeyboardRepeat(EventData eventData);
	void processKeyboardRelease(EventData eventData);

	void processMouseMovement(EventData eventData);

	void processMouseBtnPress(EventData eventData);
	void processMouseBtnRepeat(EventData eventData);
	void processMouseBtnRelease(EventData eventData);

	// calculates the front vector from the Camera's (updated) Euler Angles
	void updateCameraVectors();
};