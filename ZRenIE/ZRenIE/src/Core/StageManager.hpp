#pragma once

#include "Stage.hpp"

#include <stack>

// Handles stage creation, deletion, and switching, and more...
class StageManager
{
private:
	std::stack<Stage*> m_Stages;
};