#pragma once

#include "Character.hpp"

#include "Renderer.hpp"

#include "InputManager.hpp"

#include "FlyCamera.hpp"

#include <memory>

class World : public Character
{
public:
	World(const nlohmann::json& worldData);
	~World();

	void Update() override;
	void Render(std::shared_ptr<Renderer> renderer) override;
};