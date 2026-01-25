#pragma once

#include "Panel.hpp"

#include "../../World.hpp"

#include <map>

class HierarchyPanel : public Panel
{
private:
	std::shared_ptr<World> m_World;

	std::weak_ptr<Character> m_SelectedCharacter;

public:
	std::weak_ptr<Character> Render();

	void AssignWorldPtr(std::shared_ptr<World> worldPtr);

protected:
	void checkForInput() override;

private:
	void DisplayChildren(const std::map<std::string, std::shared_ptr<Character>>& children);
};