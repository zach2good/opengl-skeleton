#pragma once

#include "../common.h"

#include "../core/Input.h"

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

private:
	SDL_Window *m_Window;
	SDL_GLContext m_Context;
	Input m_Input;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};