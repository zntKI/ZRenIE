#pragma once

#include "Framebuffer.hpp"
#include "../Events/Observer.hpp"

class ImGuiFramebuffer : public Framebuffer, public Observer
{
public:
	using Framebuffer::Framebuffer;

	// Inherited via Observer
	void OnNotify(Event event) override;
};