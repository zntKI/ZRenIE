#pragma once

#include "Trait.hpp"

#include <glm/glm.hpp>

class TMaterial : public Trait
{
public:
	virtual void Bind(const glm::mat4& mvpMatrix) = 0;
};