#include "World.hpp"

#include "Traits/TBoxMesh.hpp"
#include "Traits/TColorMaterial.hpp"

World::World()
{
	Character* newCharacter = new Character();

	Trait* simpleShapeTrait = new TBoxMesh();
	newCharacter->AddTrait(simpleShapeTrait);

	Trait* anotherShapeTrait = new TColorMaterial();
	newCharacter->AddTrait(anotherShapeTrait);

	AddChild(newCharacter);
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