#include "TColorMaterial.hpp"

#include <glad/glad.h>

Shader* TColorMaterial::m_Shader = nullptr;

TColorMaterial::TColorMaterial(const glm::vec3& color)
	: m_Color(color)
{
	m_Shader = new Shader("src/Shaders/Color/colorVS.glsl", "src/Shaders/Color/colorFS.glsl");
	m_Shader->setVec3("u_Color", m_Color);
}

void TColorMaterial::Bind()
{
	m_Shader->use();
	m_Shader->setVec3("objectColor", m_Color);
}