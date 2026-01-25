#include "Stage.hpp"

#include "Traits/TModel.hpp"
#include "Traits/TColorMaterial.hpp"
#include "Traits/TTextureMaterial.hpp"

#include "Character.hpp"

Stage::Stage(const StageConfig& stageConfig)
	: m_Camera(std::make_shared<FlyCamera>(glm::vec3(0.f, 0.f, 3.f))),
	m_Renderer(nullptr)
{
	RendererConfig editedRendererConfig = stageConfig.rendererConfig;
	editedRendererConfig.m_WorldCamera = m_Camera;
	m_Renderer = std::make_shared<Renderer>(editedRendererConfig);

	initialize(stageConfig.worldConfigData);
}

void Stage::initialize(const nlohmann::json& worldConfigData)
{
	m_World = std::make_shared<World>(worldConfigData["worldCharacter"]);
	//m_World->m_Root = m_World;
	m_World->m_Characters.emplace(m_World->GetIdCopy(), m_World);

	for (auto& characterData : worldConfigData["characters"])
	{
		std::shared_ptr<Character> character = std::make_shared<Character>(characterData);
		m_World->RegisterChild(character);
		character->Initialize(characterData, m_World);
	}
}

Stage::~Stage()
{
}

void Stage::Update()
{
	m_World->Update();
}

void Stage::Render()
{
	m_Renderer->PreRender();

	m_World->Render(m_Renderer);

	m_Renderer->PostRender();
}

std::shared_ptr<FlyCamera> Stage::GetCameraPtr() const
{
	return m_Camera;
}

std::shared_ptr<Renderer> Stage::GetRendererPtr() const
{
	return m_Renderer;
}

std::shared_ptr<World> Stage::GetWorldPtr() const
{
	return m_World;
}
