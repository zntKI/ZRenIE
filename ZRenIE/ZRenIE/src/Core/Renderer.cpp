#include "Renderer.hpp"

#include "Traits/TBoxMesh.hpp"
#include "Traits/TColorMaterial.hpp"

#include <glad/glad.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(World* world)
{
	glClearColor(0.f, 64.f, 128.f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto& child : world->m_Children)
	{
		TBoxMesh* boxMeshTrait = nullptr;
		TColorMaterial* colorMaterialTrait = nullptr;
		for (auto& trait : child->m_Traits)
		{
			TBoxMesh* exBoxMeshTrait = dynamic_cast<TBoxMesh*>(trait);
			if (exBoxMeshTrait)
			{
				boxMeshTrait = exBoxMeshTrait;
			}
			TColorMaterial* exColorMaterialTrait = dynamic_cast<TColorMaterial*>(trait);
			if (exColorMaterialTrait)
			{
				colorMaterialTrait = exColorMaterialTrait;
			}
		}

		colorMaterialTrait->Bind();

		boxMeshTrait->Bind();
		glDrawElements(GL_TRIANGLES, boxMeshTrait->GetIndexCount(), GL_UNSIGNED_INT, 0);
	}
}