#pragma once

#include "TMaterial.hpp"
#include "../../Utility/Shader.hpp"

#include <vector>

struct Texture
{
	uint32_t id;
	//std::string type;
	std::string path;
};

class TTextureMaterial : public TMaterial
{
private:
	static std::unique_ptr<Shader> m_Shader;

	static std::vector<Texture> m_TexturesLoaded;

	Texture m_Texture;

public:
	TTextureMaterial(const std::string& texturePath);

	void Bind(const glm::mat4& mvpMatrix) override;

private:
	Texture& textureFromFile(const std::string& path, bool gamma = false);
};