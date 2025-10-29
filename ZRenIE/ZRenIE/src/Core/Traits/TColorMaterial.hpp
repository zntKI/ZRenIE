#pragma once

#include "TMaterial.hpp"
#include "../../Utility/Shader.hpp"

#include <glm/glm.hpp>

class TColorMaterial : public TMaterial
{
private:
	static Shader* m_Shader;

	glm::vec3 m_Color;

public:
	TColorMaterial(const glm::vec3& color = glm::vec3(1.f, 0.f, 1.f));

	void Bind() override;
};