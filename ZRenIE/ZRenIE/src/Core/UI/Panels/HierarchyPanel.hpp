#pragma once

#include "Panel.hpp"

class HierarchyPanel : public Panel
{
public:
	void Render();

protected:
	void checkForInput() override;
};