#include "Framebuffer.h"

Framebuffer::Framebuffer(GLuint w, GLuint h)
{
	screenWidth = w;
	screenHeight = h;
}

Framebuffer::~Framebuffer()
{
}

void Framebuffer::Bind()
{

}

void Framebuffer::Unbind()
{

}

void Framebuffer::RenderWithShader(ShaderProgram* shader)
{

}

void Framebuffer::Render()
{

}

GLuint Framebuffer::generateAttachmentTexture(GLboolean depth, GLboolean stencil)
{
	GLuint textureID;

	return textureID;
}