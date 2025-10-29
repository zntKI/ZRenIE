#pragma once

#include "World.hpp"
#include "Renderer.hpp"

// Abstract representation of a game stage or level/menu
// TODO: Think about applying the correct design pattern here (TypeObject/Prototype/Subclass Sandbox)
class Stage
{
private:
	World m_World;
	Renderer m_Renderer;

public:
	Stage();
	~Stage();

	void Update();
	void Render();

private:
	void initialize();
};