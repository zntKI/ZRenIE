#pragma once

#include "Character.hpp"

#include "Renderer.hpp"

#include "InputManager.hpp"

#include "FlyCamera.hpp"

#include <memory>

class World : public Character
{
private:
	std::shared_ptr<FlyCamera> m_Camera;

public:
	World(InputManager& inputManager);
	~World();

	void Update() override;
	void Render(Renderer& renderer) override;

	std::shared_ptr<FlyCamera> GetCameraPtr() const;
};