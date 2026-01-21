#include "World.hpp"

#include "Traits/TModel.hpp"

World::World(const nlohmann::json& worldData)
	: Character(worldData)
{
}

World::~World()
{
}

void World::Update()
{
	updateChildren();
}

void World::Render(std::shared_ptr<Renderer> renderer)
{
	renderChildren(renderer);
}

void World::AdjustHierarchy(std::string moveToId, std::string moveOfId)
{
	std::shared_ptr<Character> parentCharacter = m_Characters.find(moveToId)->second;
	std::shared_ptr<Character> childCharacter = m_Characters.find(moveOfId)->second;
	if (!parentCharacter || ! childCharacter)
	{
		Utils::logError("Invalid character Id!");
		return;
	}

	parentCharacter->AddChild(childCharacter);
}