#pragma once

#include "Panel.hpp"

#include "../../Events/Sender.hpp"

class StagePanel : public Panel, public Sender
{
public:
	void render();
	void processInput() override;
};