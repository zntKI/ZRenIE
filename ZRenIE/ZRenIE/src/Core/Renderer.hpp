#pragma once

#include "FlyCamera.hpp"
#include "Framebuffer.hpp"

#include <memory>

class Character;

class Renderer : public Observer
{
private:
	std::shared_ptr<FlyCamera> m_WorldCamera;

	std::shared_ptr<Framebuffer> m_ImGuiTexFramebuffer;

public:
	Renderer(std::shared_ptr<FlyCamera> worldCamera);
	~Renderer();

	bool PreRender();
	void Render(std::shared_ptr<Character> character);
	void PostRender();

	unsigned int GetRenderResultTexId() const;

	// Inherited via Observer
	void OnNotify(Event event) override;
};