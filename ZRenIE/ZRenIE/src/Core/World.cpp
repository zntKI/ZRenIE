#include "World.hpp"

#include "Traits/TModel.hpp"

World::World()
{
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