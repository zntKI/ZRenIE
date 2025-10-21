#pragma once

#include "Trait.hpp"

#include <glm/glm.hpp>

class TTransform : public Trait
{
private:
	glm::vec3 m_Position;
	glm::vec3 m_Rotation;
	glm::vec3 m_Scale;

public:
	TTransform();

	void Update() override;
};