#pragma once

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <stdio.h>

class Window
{
public:
	Window(const char* title, int width, int height);
	~Window();

	void init();
	void cleanUp();

	void clear();
	void swap();

	bool isCloseRequested();
	void requestClose();

	SDL_Window* getWindow();
	SDL_GLContext getContext();

private:
	SDL_Window *m_Window;
	SDL_GLContext m_Context;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};
