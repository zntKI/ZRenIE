#pragma once

#include "World.hpp"

class Renderer
{
public:
	Renderer();
	~Renderer();

	void Render(World* world);
};