#include "Framebuffer.hpp"

#include "Application.hpp"

Framebuffer::Framebuffer(unsigned int windowWidth, unsigned int windowHeight)
	: WindowWidth(windowWidth), WindowHeight(windowHeight)
{
	// generate framebuffer
	glGenFramebuffers(1, &m_FrameBufferId);
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);

	// generate texture
	glGenTextures(1, &m_TexColorBufferId);
	glBindTexture(GL_TEXTURE_2D, m_TexColorBufferId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WindowWidth, WindowHeight, 0, GL_RGB,
		GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// attach it to currently bound framebuffer object
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_TexColorBufferId, 0);

	glBindTexture(GL_TEXTURE_2D, 0);

	// generate render buffer
	glGenRenderbuffers(1, &m_RenderBufferId);
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WindowWidth, WindowHeight);

	// attach it to currently bound framebuffer object
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, m_RenderBufferId);

	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		Utils::logMessage("ERROR::FRAMEBUFFER::Framebuffer is not complete!\n");
	}
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

Framebuffer::~Framebuffer()
{
	if (m_RenderBufferId)
		glDeleteRenderbuffers(1, &m_RenderBufferId);
	if (m_TexColorBufferId)
		glDeleteTextures(1, &m_TexColorBufferId);
	if (m_FrameBufferId)
		glDeleteFramebuffers(1, &m_FrameBufferId);
}

void Framebuffer::Resize(unsigned int newWindowWidth, unsigned int newWindowHeight)
{
	WindowWidth = newWindowWidth;
	WindowHeight = newWindowHeight;

	// Resize color texture
	glBindTexture(GL_TEXTURE_2D, m_TexColorBufferId);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WindowWidth, WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
	glBindTexture(GL_TEXTURE_2D, 0);

	// Resize depth-stencil renderbuffer
	glBindRenderbuffer(GL_RENDERBUFFER, m_RenderBufferId);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, WindowWidth, WindowHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
}

void Framebuffer::Use()
{
	glBindFramebuffer(GL_FRAMEBUFFER, m_FrameBufferId);
	glViewport(0, 0, WindowWidth, WindowHeight);
}

void Framebuffer::Unuse()
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glViewport(0, 0, Application::GetScreenWidth(), Application::GetScreenHeight());
}

float Framebuffer::GetAspectRatio() const
{
	return WindowWidth / (float)WindowHeight;
}

unsigned int Framebuffer::GetTexId() const
{
	return m_TexColorBufferId;
}