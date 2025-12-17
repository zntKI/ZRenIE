#include "World.hpp"

#include "Traits/TModel.hpp"

World::World(InputManager& inputManager)
	: m_Camera(std::make_shared<FlyCamera>())
{
	AddChild(std::dynamic_pointer_cast<Character>(m_Camera));
	inputManager.AddObserver(std::dynamic_pointer_cast<Observer>(m_Camera));
}

World::~World()
{
}

void World::Update()
{
	updateChildren();
}

void World::Render(std::shared_ptr<Renderer> renderer)
{
	renderChildren(renderer);
}

std::shared_ptr<FlyCamera> World::GetCameraPtr() const
{
	return m_Camera;
}