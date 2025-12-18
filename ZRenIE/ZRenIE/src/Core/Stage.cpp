#include "Stage.hpp"

#include "Traits/TModel.hpp"
#include "Traits/TColorMaterial.hpp"
#include "Traits/TTextureMaterial.hpp"

#include "Character.hpp"

Stage::Stage()
	: m_Camera(std::make_shared<FlyCamera>(glm::vec3(0.f, 0.f, 3.f))),
	m_Renderer(std::make_shared<Renderer>(m_Camera))
{
	initialize();
}

Stage::~Stage()
{
}

void Stage::initialize()
{
	std::shared_ptr<Character> cube = std::make_shared<Character>();

	std::shared_ptr<TModel> cubeModel = std::make_shared<TModel>("Assets/Models/Basic/cube.obj");
	cube->AddTrait(cubeModel);

	//std::shared_ptr<TMaterial> cubeMaterial = std::make_shared<TColorMaterial>(glm::vec3(1.f, 0.f, 0.f));
	std::shared_ptr<TMaterial> cubeMaterial = std::make_shared<TTextureMaterial>("Assets/Textures/container2.png");
	cube->AddTrait(cubeMaterial);

	for (auto& mesh : cubeModel->m_Meshes)
	{
		mesh->m_Material = cubeMaterial;
	}

	m_World.AddChild(cube);
}

void Stage::Update()
{
	m_World.Update();
}

void Stage::Render()
{
	if (m_Renderer->PreRender())
	{
		m_World.Render(m_Renderer);
		m_Renderer->PostRender();
	}
}

unsigned int Stage::GetRenderResultTexId() const
{
	return m_Renderer->GetRenderResultTexId();
}

std::shared_ptr<FlyCamera> Stage::GetCameraPtr() const
{
	return m_Camera;
}

std::shared_ptr<Renderer> Stage::GetRendererPtr() const
{
	return m_Renderer;
}
