#pragma once

#include "FlyCamera.hpp"

#include <memory>

class Character;

class Renderer
{
private:
	std::shared_ptr<FlyCamera> m_WorldCamera;

public:
	Renderer(std::shared_ptr<FlyCamera> worldCamera);
	~Renderer();

	void SetupRender();

	void Render(std::shared_ptr<Character> character);
};