#pragma once

#include "World.hpp"
#include "Renderer.hpp"
#include "FlyCamera.hpp"

#include "InputManager.hpp"

#include <memory>

// Abstract representation of a game stage or level/menu
// TODO: Think about applying the correct design pattern here (TypeObject/Prototype/Subclass Sandbox)
class Stage
{
private:
	std::shared_ptr<FlyCamera> m_Camera;

	World m_World;
	std::shared_ptr<Renderer> m_Renderer;

public:
	Stage();
	~Stage();

	void Update();
	void Render();

	std::shared_ptr<FlyCamera> GetCameraPtr() const;

private:
	void initialize();
};