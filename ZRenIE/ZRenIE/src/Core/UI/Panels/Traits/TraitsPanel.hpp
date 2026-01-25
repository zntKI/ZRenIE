#pragma once

#include "../Panel.hpp"

#include "../../../Character.hpp"

#include <memory>

class TraitsPanel : public Panel
{
public:
	void Render(std::weak_ptr<Character> charForRenderTraits);

protected:
	// Inherited via Panel
	void checkForInput() override;
};