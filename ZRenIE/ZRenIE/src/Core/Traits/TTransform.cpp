#include "TTransform.hpp"

#include <glm/ext/matrix_transform.hpp>

TTransform::TTransform()
	: m_Position(0.0f, 0.0f, 0.0f),
	m_Rotation(0.0f, 0.0f, 0.0f),
	m_Scale(1.0f, 1.0f, 1.0f)
{
}

glm::mat4 TTransform::GetModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.f);

	model = glm::translate(model, m_Position);

	glm::mat4 rotationMat =
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)) * // yaw
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)) * // pitch
		glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // row
	model = model * rotationMat;

	model = glm::scale(model, glm::vec3(m_Scale[0], m_Scale[1], m_Scale[2]));

	return model;
}

//void TTransform::Update()
//{
//}