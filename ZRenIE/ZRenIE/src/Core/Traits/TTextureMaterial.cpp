#include "TTextureMaterial.hpp"

#include <stb_image.h>

std::unique_ptr<Shader> TTextureMaterial::m_Shader = nullptr;

std::vector<Texture> TTextureMaterial::m_TexturesLoaded;

TTextureMaterial::TTextureMaterial(const std::string& texturePath)
	: m_Texture(textureFromFile(texturePath))
{
	if (!m_Shader) // Lazy init to avoid creation before gl context exists
		m_Shader = std::make_unique<Shader>("src/Shaders/Texture/textureVS.glsl", "src/Shaders/Texture/textureFS.glsl");
}

void TTextureMaterial::Bind(const glm::mat4& mvpMatrix)
{
	m_Shader->use();

	m_Shader->setMatrix4("u_MVP", mvpMatrix);

	m_Shader->setInt("u_Texture", 0);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_Texture.id);
}

void TTextureMaterial::Render()
{
	if (textureView.Render(m_Texture.id, m_Texture.path))
	{
		m_Texture = textureFromFile(m_Texture.path);
	}
}

Texture& TTextureMaterial::textureFromFile(const std::string& path, bool gamma)
{
	for (auto& textureLoaded : m_TexturesLoaded)
	{
		if (textureLoaded.path == path)
		{
			return textureLoaded;
		}
	}

	uint32_t textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
	if (data) {
		GLenum format;
		if (nrComponents == 1)
			format = GL_RED;
		else if (nrComponents == 3)
			format = GL_RGB;
		else if (nrComponents == 4)
			format = GL_RGBA;

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else {
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	Texture texture;
	texture.id = textureID;
	texture.path = path;

	m_TexturesLoaded.push_back(texture);

	return texture;
}