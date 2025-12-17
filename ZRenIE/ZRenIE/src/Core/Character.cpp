#include "Character.hpp"

#include "Renderer.hpp"

void Character::updateChildren()
{
	for (auto& child : m_Children)
	{
		child->Update();
	}
}

void Character::renderChildren(std::shared_ptr<Renderer> renderer)
{
	for (auto& child : m_Children)
	{
		child->Render(renderer);
	}
}

Character::Character()
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
	updateChildren();
}

void Character::Render(std::shared_ptr<Renderer> renderer)
{
	renderer->Render(shared_from_this());

	renderChildren(renderer);
}

void Character::AddChild(const std::shared_ptr<Character>& child)
{
	m_Children.push_back(child);
	child->m_Parent = weak_from_this();
}

void Character::AddTrait(const std::shared_ptr<Trait>& newTrait)
{
	m_Traits.push_back(newTrait);
}