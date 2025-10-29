#include "World.hpp"

World::World()
{
}

World::~World()
{
}

void World::Update()
{
	for (auto& child : m_Children)
	{
		child->Update();
	}
}

void World::Render()
{
	for (auto& child : m_Children)
	{
		child->Render();
	}
}