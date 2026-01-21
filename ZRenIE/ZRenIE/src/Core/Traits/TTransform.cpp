#include "TTransform.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include <glm/gtx/euler_angles.hpp>
#include <glm/gtc/quaternion.hpp>

TTransform::TTransform(const nlohmann::json& transformData)
	: m_Local(transformData),
	m_LocalMatrix(m_Local.GetTransformMatrix()),
	m_WorldMatrix(CalculateWorldMatrix(glm::mat4(1.f)))
{
}

glm::mat4 TTransform::CalculateLocalMatrix(const glm::mat4& parentWorldMatrix)
{
	m_LocalMatrix = glm::inverse(parentWorldMatrix) * m_WorldMatrix;
	m_Local = fromMatrix(m_LocalMatrix);

	return m_LocalMatrix;
}

glm::mat4 TTransform::CalculateWorldMatrix(const glm::mat4& parentWorldMatrix)
{
	m_WorldMatrix = parentWorldMatrix * m_LocalMatrix;
	return m_WorldMatrix;
}

void TTransform::UpdateLocalTransform(const TransformProperties& newLocalTransform)
{
	m_Local = newLocalTransform;
	m_LocalMatrix = m_Local.GetTransformMatrix();
}

glm::mat4 TTransform::GetWorldMatrix() const
{
	return m_WorldMatrix;
}

TransformProperties TTransform::GetLocalTransformPropertiesCopy() const
{
	return m_Local;
}

TransformProperties TTransform::fromMatrix(const glm::mat4& m)
{
	// Decompose: m = T * R * S
	glm::vec3 scale, translation, skew;
	glm::vec4 perspective;
	glm::quat orientation;
	glm::mat4 M = m;

	if (!glm::decompose(M, scale, orientation, translation, skew, perspective))
	{
		// Fallback to identity if decomposition fails
		return TransformProperties{};
	}

	// Convert rotation quaternion to Euler angles in degrees
	glm::vec3 eulerRadians = glm::eulerAngles(glm::normalize(orientation)); // XYZ order
	glm::vec3 eulerDegrees = glm::degrees(eulerRadians);

	return TransformProperties(translation, eulerDegrees, scale);
}

//void TTransform::Update()
//{
//}