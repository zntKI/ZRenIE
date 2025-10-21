#pragma once

#include "TTransform.hpp"

#include <vector>

class Character
{
public:
	void Update();
	void Render();

private:
	TTransform* m_TransformTrait;
};