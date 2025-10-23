#pragma once

#include "Trait.hpp"

#include <vector>

class TBoxMesh : public Trait
{
private:
	unsigned int m_VAO;

	static unsigned int m_VerticesVBO;
	static unsigned int m_EBO;

	static float m_Vertices[];
	static unsigned int m_Indices[];

public:
	TBoxMesh();

	void Update() override;

	void Bind();
	unsigned int GetIndexCount() const;
};