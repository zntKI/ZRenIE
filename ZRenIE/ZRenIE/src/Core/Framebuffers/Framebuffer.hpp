#pragma once

#include "../Platform.hpp"

#include "../../Utility/Utils.hpp"

enum class FramebufferTypes
{
	BASE,
	IMGUI,
};

class Framebuffer
{
protected:
	unsigned int m_FrameBufferId;

	bool m_Initialized;

	unsigned int m_TexColorBufferId;
	unsigned int m_RenderBufferId;

	unsigned int m_WindowWidth, m_WindowHeight;

public:
	Framebuffer();
	Framebuffer(unsigned int windowWidth, unsigned int windowHeight);
	void Initialize(unsigned int windowWidth, unsigned int windowHeight);
	virtual ~Framebuffer();

	void Resize(unsigned int newWindowWidth, unsigned int newWindowHeight);

	void Use();
	void Unuse(unsigned int newViewportWidth, unsigned int newViewportHeight);

	float GetAspectRatio() const;

	unsigned int GetTexId() const;

protected:
	bool isInitialized() const;
};