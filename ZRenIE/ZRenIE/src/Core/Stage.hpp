#pragma once

#include "World.hpp"
#include "Renderer.hpp"

#include "InputManager.hpp"

// Abstract representation of a game stage or level/menu
// TODO: Think about applying the correct design pattern here (TypeObject/Prototype/Subclass Sandbox)
class Stage
{
private:
	World m_World;
	Renderer m_Renderer;

public:
	Stage(InputManager& inputManager);
	~Stage();

	void Update();
	void Render();

private:
	void initialize();
};