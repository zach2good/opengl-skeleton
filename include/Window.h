#pragma once

#include <glad\glad.h>
#include <SDL.h>

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

	inline int getWidth() { return WIDTH; }
	inline int getHeight() { return HEIGHT; }

private:
	SDL_Window *m_Window;
	SDL_GLContext m_Context;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};