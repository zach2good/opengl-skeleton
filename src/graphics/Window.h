#pragma once

#include "../common.h"

#include "../core/Input.h"

#include "../core/Timer.h"

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void init();
	void cleanUp();

	void update();
	void clear();
	void swap();

	bool isCloseRequested();
	void requestClose();

	SDL_Window* getWindow() const;
	SDL_GLContext getContext();

	int getWidth() const { return WIDTH; }
	int getHeight() const { return HEIGHT; }
	float getAspect() const	{ return float(WIDTH) / float(HEIGHT); }

	void setGLDepthTest(bool setting)
	{
		setting ?
		glEnable(GL_DEPTH_TEST) :
		glDisable(GL_DEPTH_TEST);
	}

	void setGLMultisample(bool setting)
	{
		setting ?
			glEnable(GL_MULTISAMPLE) :
			glDisable(GL_MULTISAMPLE);
	}

	void setGLCullFace(bool setting)
	{
		setting ?
			glEnable(GL_CULL_FACE) :
			glDisable(GL_CULL_FACE);
	}

	void setGLBlend(bool setting)
	{
		glCullFace(GL_BACK);
		setting ?
			glEnable(GL_BLEND) :
			glDisable(GL_BLEND);
	}

	void setGLGammaCorrection(bool setting)
	{
		setting ?
			glEnable(GL_FRAMEBUFFER_SRGB) :
			glDisable(GL_FRAMEBUFFER_SRGB);
	}

private:
	SDL_Window *m_Window;
	SDL_GLContext m_Context;

	SDL_Event event;

	double startTime;
	double endTime;
	double renderTime;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};