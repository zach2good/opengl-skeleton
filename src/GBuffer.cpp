#include "GBuffer.h"

GBuffer::GBuffer()
{
	m_fbo = 0;
	m_tex = 0;
	m_depth = 0;
}

GBuffer::~GBuffer()
{
	glDeleteFramebuffers(1, &m_fbo);
}

void GBuffer::Init(unsigned int WindowWidth, unsigned int WindowHeight)
{
	glGenFramebuffers(1, &m_fbo);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);

	glGenTextures(1, &m_tex);	
	glBindTexture(GL_TEXTURE_2D, m_tex);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, WindowWidth, WindowHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

	glGenRenderbuffers(1, &m_depth);
	glBindRenderbuffer(GL_RENDERBUFFER, m_depth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, WindowWidth, WindowHeight);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depth);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
}


void GBuffer::StartFrame()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
}

void GBuffer::EndFrame()
{
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glBindFramebuffer(GL_READ_FRAMEBUFFER, m_fbo);
}

