#pragma once

#include "Platform.hpp"

#include "../Utility/Utils.hpp"

class Framebuffer
{
private:
	unsigned int m_FrameBufferId;

	unsigned int m_TexColorBufferId;
	unsigned int m_RenderBufferId;

	unsigned int WindowWidth, WindowHeight;

public:
	Framebuffer(unsigned int windowWidth, unsigned int windowHeight);
	~Framebuffer();

	void Resize(unsigned int newWindowWidth, unsigned int newWindowHeight);

	void Use();
	void Unuse();

	float GetAspectRatio() const;

	unsigned int GetTexId() const;
};