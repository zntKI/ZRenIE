#pragma once

#include "Trait.hpp"

#include <glm/glm.hpp>

class TColorMaterial : public Trait
{
private:
	glm::vec3 m_Color;

public:
	TColorMaterial(const glm::vec3& color = glm::vec3(1.f, 0.f, 1.f));

	void Update() override;
};