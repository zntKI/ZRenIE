#include "TTransform.hpp"

#include <glm/ext/matrix_transform.hpp>

TTransform::TTransform(const nlohmann::json& transformData)
{
	nlohmann::json positionData = transformData["position"];
	m_LocalPosition = glm::vec3(positionData["x"], positionData["y"], positionData["z"]);
	nlohmann::json rotationData = transformData["rotation"];
	m_LocalRotation = glm::vec3(rotationData["x"], rotationData["y"], rotationData["z"]);
	nlohmann::json scaleData = transformData["scale"];
	m_LocalScale = glm::vec3(scaleData["x"], scaleData["y"], scaleData["z"]);

	m_GlobalPosition = m_LocalPosition;
	m_GlobalRotation = m_LocalRotation;
	m_GlobalScale = m_LocalScale;
}

glm::mat4 TTransform::GetModelMatrix() const
{
	glm::mat4 model = glm::mat4(1.f);

	model = glm::translate(model, m_LocalPosition);

	glm::mat4 rotationMat =
		glm::rotate(glm::mat4(1.0f), glm::radians(m_LocalRotation[1]), glm::vec3(0.0f, 1.0f, 0.0f)) * // yaw
		glm::rotate(glm::mat4(1.0f), glm::radians(m_LocalRotation[0]), glm::vec3(1.0f, 0.0f, 0.0f)) * // pitch
		glm::rotate(glm::mat4(1.0f), glm::radians(m_LocalRotation[2]), glm::vec3(0.0f, 0.0f, 1.0f)); // row
	model = model * rotationMat;

	model = glm::scale(model, glm::vec3(m_LocalScale[0], m_LocalScale[1], m_LocalScale[2]));

	return model;
}

//void TTransform::Update()
//{
//}