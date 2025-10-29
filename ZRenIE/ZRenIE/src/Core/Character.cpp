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
	//m_TransformTrait.Update();
	for (auto& trait : m_Traits)
	{
		// TODO: Do smth
	}
}

void Character::Render()
{
}

void Character::AddChild(const std::shared_ptr<Character>& child)
{
	m_Children.push_back(child);
	child->m_Parent = this;
}

void Character::AddTrait(const std::shared_ptr<Trait>& newTrait)
{
	m_Traits.push_back(newTrait);
}