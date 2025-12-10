#pragma once

#include "Traits/Trait.hpp"
#include "Traits/TTransform.hpp"

#include <string>
#include <map>
#include <vector>
#include <memory>

class Renderer;

class Character : public std::enable_shared_from_this<Character>
{
	friend class Renderer;

protected:
	std::weak_ptr<Character> m_Parent;
	std::vector<std::shared_ptr<Character>> m_Children;

	TTransform m_TransformTrait;
	std::vector<std::shared_ptr<Trait>> m_Traits;

public:
	Character();
	~Character();

	virtual void Update();
	virtual void Render(Renderer& renderer);

	void AddChild(const std::shared_ptr<Character>& child);

	void AddTrait(const std::shared_ptr<Trait>& newTrait);

protected:
	void updateChildren();
	void renderChildren(Renderer& renderer);
};