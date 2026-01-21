#pragma once

#include "Panel.hpp"

#include "../../World.hpp"

#include <map>

class HierarchyPanel : public Panel
{
private:
	std::shared_ptr<World> m_World;

public:
	void Render();

	void AssignWorldPtr(std::shared_ptr<World> worldPtr);

protected:
	void checkForInput() override;

private:
	void DisplayChildren(const std::map<std::string, std::shared_ptr<Character>>& children) const;
};