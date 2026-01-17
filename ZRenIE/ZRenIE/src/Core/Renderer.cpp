#include "Renderer.hpp"

#include "Application.hpp"

#include "Framebuffers/ImGuiFramebuffer.hpp"

#include "Character.hpp"
#include "Traits/TModel.hpp"

#include "../Utility/Utils.hpp"

Renderer::Renderer(const RendererConfig& rendererConfig)
	: m_ImGuiFramebuffer(
		rendererConfig.shouldRenderToFramebuffer ?
		std::make_shared<ImGuiFramebuffer>(
			Application::GetScreenWidth(), Application::GetScreenHeight()
		) :
		nullptr
	)
{
	m_WorldCamera = rendererConfig.m_WorldCamera;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}

Renderer::~Renderer()
{
}

void Renderer::PreRender()
{
	if (m_ImGuiFramebuffer)
	{
		m_ImGuiFramebuffer->Use();
	}

	glClearColor(0.f, 0.25f, .5f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::Render(std::shared_ptr<Character> character)
{
	std::shared_ptr<TTransform> transformTrait = character->m_TransformTrait;
	std::shared_ptr<TModel> modelTrait;
	for (auto& trait : character->m_Traits)
	{
		if (auto tryModelTrait = std::dynamic_pointer_cast<TModel>(trait);
			tryModelTrait != nullptr)
			modelTrait = tryModelTrait;
	}
	if (!modelTrait)
		return;

	glm::mat4 model = transformTrait->GetModelMatrix();
	glm::mat4 view = m_WorldCamera->GetViewMatrix();
	glm::mat4 projection = m_WorldCamera->GetProjMatrix(m_ImGuiFramebuffer->GetAspectRatio());

	modelTrait->Draw(projection * view * model);
}

void Renderer::PostRender()
{
	if (m_ImGuiFramebuffer)
	{
		m_ImGuiFramebuffer->Unuse(Application::GetScreenWidth(), Application::GetScreenHeight());
	}
}

std::shared_ptr<Framebuffer> Renderer::GetImGuiFramebuffer() const
{
	if (!m_ImGuiFramebuffer)
	{
		Utils::logMessage("Framebuffer was not created previously!");
		return 0;
	}
	return m_ImGuiFramebuffer;
}