#pragma once

#include "World.hpp"

// Abstract representation of a game stage or level/menu
// TODO: Think about applying the correct design pattern here (TypeObject/Prototype/Subclass Sandbox)
class Stage
{
public:
	Stage();
	~Stage();

	void Update();

private:
	World m_World;
};