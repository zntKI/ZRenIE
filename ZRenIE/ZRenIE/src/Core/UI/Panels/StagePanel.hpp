#pragma once

#include "Panel.hpp"

#include "../../Events/Observer.hpp"
#include "../../Events/Sender.hpp"

class StagePanel : public Panel, public Observer, public Sender
{
public:
	void render();

	// Inherited via Observer
	void OnNotify(Event event) override;
};