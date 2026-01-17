#pragma once

#include "Trait.hpp"

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

class TTransform : public Trait
{
private:
	glm::vec3 m_LocalPosition;
	glm::vec3 m_LocalRotation;
	glm::vec3 m_LocalScale;

	glm::vec3 m_GlobalPosition;
	glm::vec3 m_GlobalRotation;
	glm::vec3 m_GlobalScale;

public:
	TTransform(const nlohmann::json& transformData);

	glm::mat4 GetModelMatrix() const;
};