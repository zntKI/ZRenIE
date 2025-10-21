#include "Character.hpp"

Character::Character()
	: m_Parent(nullptr)
{
}

Character::~Character()
{
}

void Character::Update()
{
	m_TransformTrait.Update();
	for (auto& trait : m_Traits)
	{
		trait->Update();
	}
}

void Character::Render()
{
}

void Character::AddChild(Character* child)
{
	m_Children.push_back(child);
	child->m_Parent = this;
}

void Character::AddTrait(Trait* newTrait)
{
	m_Traits.push_back(newTrait);
}