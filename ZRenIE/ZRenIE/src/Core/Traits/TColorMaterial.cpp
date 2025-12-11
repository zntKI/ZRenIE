#include "TColorMaterial.hpp"

#include "../Platform.hpp"

std::unique_ptr<Shader> TColorMaterial::m_Shader = nullptr;

TColorMaterial::TColorMaterial(const glm::vec3& color)
	: m_Color(color)
{
	if (!m_Shader) // Lazy init to avoid creation before gl context exists
		m_Shader = std::make_unique<Shader>("src/Shaders/Color/colorVS.glsl", "src/Shaders/Color/colorFS.glsl");

	m_Shader->use();
	m_Shader->setVec3("u_Color", m_Color);
}

void TColorMaterial::Bind(const glm::mat4& mvpMatrix)
{
	m_Shader->use();

	m_Shader->setMatrix4("u_MVP", mvpMatrix);

	m_Shader->setVec3("u_Color", m_Color);
}