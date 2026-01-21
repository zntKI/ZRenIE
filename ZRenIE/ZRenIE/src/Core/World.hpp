#pragma once

#include "Character.hpp"

#include "Renderer.hpp"

#include "InputManager.hpp"

#include "FlyCamera.hpp"

#include <memory>
#include <map>

class World : public Character
{
public:
	/// <summary>
	/// All characters in the stage
	/// </summary>
	std::map<std::string, std::shared_ptr<Character>> m_Characters;

public:
	World(const nlohmann::json& worldData);
	~World();

	void Update() override;
	void Render(std::shared_ptr<Renderer> renderer) override;

	/// <summary>
	/// Hanldes moving of characters within the hierarchy
	/// </summary>
	/// <param name="moveToId">Id of the Character that is to become parent of the other</param>
	/// <param name="moveOfId">Id of the Character that is to become child of the other</param>
	void AdjustHierarchy(std::string moveToId, std::string moveOfId);
};