#pragma once

#include "Traits/Trait.hpp"
#include "Traits/TTransform.hpp"

#include <string>
#include <map>
#include <vector>

class Character
{
	friend class Renderer;
public:
	Character();
	~Character();

	void Update();
	void Render();

	void AddChild(Character* child);

	void AddTrait(Trait* newTrait);

protected:
	Character* m_Parent;
	std::vector<Character*> m_Children;

	TTransform m_TransformTrait;
	std::vector<Trait*> m_Traits;
};