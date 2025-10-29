#include "Renderer.hpp"

#include "Traits/TModel.hpp"

#include <glad/glad.h>

Renderer::Renderer()
{
}

Renderer::~Renderer()
{
}

void Renderer::Render(World* world)
{
	for (auto& child : world->m_Children)
	{
		TTransform transformTrait = child->m_TransformTrait;
		std::shared_ptr<TModel> modelTrait;
		for (auto& trait : child->m_Traits)
		{
			if (auto tryModelTrait = std::dynamic_pointer_cast<TModel>(trait);
				tryModelTrait != nullptr)
					modelTrait = tryModelTrait;
		}

		modelTrait->Draw();
	}
}

void Renderer::setupRender()
{
	glClearColor(0.f, 0.25f, .5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}