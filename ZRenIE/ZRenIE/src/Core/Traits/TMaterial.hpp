#pragma once

#include "Trait.hpp"

class TMaterial : public Trait
{
public:
	virtual void Bind() = 0;
};