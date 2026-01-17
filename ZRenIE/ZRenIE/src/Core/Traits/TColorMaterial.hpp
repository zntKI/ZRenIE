#pragma once

#include "TMaterial.hpp"
#include "../../Utility/Shader.hpp"

#include <glm/glm.hpp>

#include <nlohmann/json.hpp>

#include <memory>

class TColorMaterial : public TMaterial
{
private:
	static std::unique_ptr<Shader> m_Shader;

	glm::vec3 m_Color;

public:
	TColorMaterial(const nlohmann::json& colorData);

	void Bind(const glm::mat4& mvpMatrix) override;
};