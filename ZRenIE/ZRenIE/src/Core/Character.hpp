#pragma once

#include "Traits/Trait.hpp"
#include "Traits/TTransform.hpp"

#include <string>
#include <map>
#include <vector>
#include <memory>

class Character
{
	friend class Renderer;

protected:
	Character* m_Parent;
	std::vector<std::shared_ptr<Character>> m_Children;

	TTransform m_TransformTrait;
	std::vector<std::shared_ptr<Trait>> m_Traits;

public:
	Character();
	~Character();

	void Update();
	void Render();

	void AddChild(const std::shared_ptr<Character>& child);

	void AddTrait(const std::shared_ptr<Trait>& newTrait);
};