#include "TTransform.hpp"

#include <glm/ext/matrix_transform.hpp>

TTransform::TTransform(const nlohmann::json& transformData)
	: m_Local(transformData), m_Global(m_Local)
{
}

glm::mat4 TTransform::GetModelMatrix() const
{
	return m_Global.GetTransformMatrix();
}

const TransformProperties& TTransform::GetGlobalTransformProperties() const
{
	return m_Global;
}

void TTransform::SetGlobalTransformProperties(const TransformProperties& parent_GlobalTransformProps)
{
	m_Global = parent_GlobalTransformProps + m_Local;
}

//void TTransform::Update()
//{
//}