#include "Renderer.hpp"
#include "Character.hpp"

#include "Traits/TModel.hpp"

#include "../Utility/Utils.hpp"

#include <tuple>

Renderer::Renderer(std::shared_ptr<FlyCamera> worldCamera)
	: m_ImGuiTexFramebuffer(nullptr)
{
	m_WorldCamera = worldCamera;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Renderer::~Renderer()
{
}

bool Renderer::PreRender()
{
	if (m_ImGuiTexFramebuffer)
	{
		m_ImGuiTexFramebuffer->Use();
		glClearColor(0.f, 0.25f, .5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		return true;
	}
	return false;
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
	glm::mat4 view = m_WorldCamera->GetViewMatrix();
	glm::mat4 projection = m_WorldCamera->GetProjMatrix(m_ImGuiTexFramebuffer->GetAspectRatio());

	modelTrait->Draw(projection * view * model);
}

void Renderer::PostRender()
{
	if (m_ImGuiTexFramebuffer)
	{
		m_ImGuiTexFramebuffer->Unuse();
	}
}

unsigned int Renderer::GetRenderResultTexId() const
{
	if (!m_ImGuiTexFramebuffer)
		return 0;
	else
		return m_ImGuiTexFramebuffer->GetTexId();
}

void Renderer::OnNotify(Event event)
{
	switch (event.eventType)
	{
	case EventType::ON_WINDOW_RESIZE:
	{
		unsigned int panelWidth = static_cast<unsigned int>(get<0>(event.eventData.twoValueChange));
		unsigned int panelHeight = static_cast<unsigned int>(get<1>(event.eventData.twoValueChange));

		if (!m_ImGuiTexFramebuffer)
		{
			m_ImGuiTexFramebuffer = std::make_shared<Framebuffer>(panelWidth, panelHeight);
		}
		else
		{
			m_ImGuiTexFramebuffer->Resize(panelWidth, panelHeight);
		}
		break;
	}
	default:
		break;
	}
}