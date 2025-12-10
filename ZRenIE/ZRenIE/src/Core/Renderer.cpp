#include "Renderer.hpp"
#include "Character.hpp"

#include "Traits/TModel.hpp"
#include "Application.hpp"

Renderer::Renderer(std::shared_ptr<FlyCamera> worldCamera)
{
	m_WorldCamera = worldCamera;
}

Renderer::~Renderer()
{
}

void Renderer::SetupRender()
{
	glClearColor(0.f, 0.25f, .5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::shared_ptr<Character> character)
{
	TTransform transformTrait = character->m_TransformTrait;
	std::shared_ptr<TModel> modelTrait;
	for (auto& trait : character->m_Traits)
	{
		if (auto tryModelTrait = std::dynamic_pointer_cast<TModel>(trait);
			tryModelTrait != nullptr)
			modelTrait = tryModelTrait;
	}
	if (!modelTrait)
		return;

	glm::mat4 model = transformTrait.GetModelMatrix();
	glm::mat4 view = m_WorldCamera.get()->GetViewMatrix();
	glm::mat4 projection = glm::perspective(glm::radians(m_WorldCamera.get()->Zoom), Application::GetScreenWidth() / (float)Application::GetScreenHeight(), .1f, 100.f);

	modelTrait->Draw(projection * view * model);
}