#include "TBoxMesh.hpp"

#include <glad/glad.h>

unsigned int TBoxMesh::m_VerticesVBO = 0;
unsigned int TBoxMesh::m_EBO = 0;


float TBoxMesh::m_Vertices[] = {
		-0.5f, -0.5f, -0.5f,
		 0.5f, -0.5f, -0.5f,
		 0.5f,  0.5f, -0.5f,
		-0.5f,  0.5f, -0.5f,
		-0.5f, -0.5f,  0.5f,
		 0.5f, -0.5f,  0.5f,
		 0.5f,  0.5f,  0.5f,
		-0.5f,  0.5f,  0.5f,
};
unsigned int TBoxMesh::m_Indices[] = {
	// Front face
	0, 1, 2,
	0, 2, 3,
	// Back face
	4, 5, 6,
	4, 6, 7,
	// Left face
	4, 0, 3,
	4, 3, 7,
	// Right face
	1, 5, 6,
	1, 6, 2,
	// Top face
	3, 2, 6,
	3, 6, 7,
	// Bottom face
	0, 1, 5,
	0, 5, 4
};

TBoxMesh::TBoxMesh()
	: m_VAO(0)
{
	// Create a VAO for this instance
	glGenVertexArrays(1, &m_VAO);
	glBindVertexArray(m_VAO);

	// Ensure shared VBO exists and contains data (upload once)
	if (m_VerticesVBO == 0)
	{
		// If it doesn't exist yet, create and upload data
		glGenBuffers(1, &m_VerticesVBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(m_Vertices), m_Vertices, GL_STATIC_DRAW);
	}
	else
	{
		// If it already exists, just bind it
		glBindBuffer(GL_ARRAY_BUFFER, m_VerticesVBO);
	}

	// Set up vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Ensure shared EBO exists and contains data (upload once)
	if (m_EBO == 0)
	{
		// If it doesn't exist yet, create and upload data
		glGenBuffers(1, &m_EBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_Indices), m_Indices, GL_STATIC_DRAW);
	}
	else
	{
		// If it already exists, just bind it
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	}

	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void TBoxMesh::Update()
{
}

void TBoxMesh::Bind()
{
	glBindVertexArray(m_VAO);
}

unsigned int TBoxMesh::GetIndexCount() const
{
	return sizeof(m_Indices) / sizeof(unsigned int);
}