#pragma once

#include "TMaterial.hpp"

#include "../../Utility/Shader.hpp"

#include <glm/glm.hpp>

#include <string>
#include <vector>
#include <memory>

struct Vertex
{
	glm::vec3 m_Position;
	glm::vec3 m_Normal;
	glm::vec2 m_TexCoords;
};

class Mesh
{
public:
	// mesh data
	std::vector<Vertex> m_Vertices;
	std::vector<uint32_t> m_Indices;

	std::shared_ptr<TMaterial> m_Material;

	Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices);
	void Draw(const glm::mat4& mvpMatrix);

	uint32_t m_VAO;

private:
	// render data
	uint32_t m_VBO, m_EBO;

	void setupMesh();
};