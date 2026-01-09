#pragma once

#include "FlyCamera.hpp"
#include "Framebuffers/Framebuffer.hpp"

#include <memory>

class Character;

struct RendererConfig
{
	std::shared_ptr<FlyCamera> m_WorldCamera;

	bool shouldRenderToFramebuffer;
};

class Renderer
{
private:
	std::shared_ptr<FlyCamera> m_WorldCamera;

	// ImGui framebuffer
	std::shared_ptr<Framebuffer> m_ImGuiFramebuffer;

public:
	Renderer(const RendererConfig& rendererConfig);
	~Renderer();

	void PreRender();
	void Render(std::shared_ptr<Character> character);
	void PostRender();

	std::shared_ptr<Framebuffer> GetImGuiFramebuffer() const;
};