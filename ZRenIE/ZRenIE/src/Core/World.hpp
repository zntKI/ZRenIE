#pragma once

#include "Character.hpp"

class World : public Character
{
public:
	World();
	~World();

	void Update();
	void Render();
};