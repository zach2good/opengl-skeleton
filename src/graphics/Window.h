#pragma once

#include <SDL.h>
#include <glad\glad.h>
#include <stdio.h>

#include "../core/Input.h"

//class Input;

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

	SDL_Window* getWindow();
	SDL_GLContext getContext();

	inline int getWidth() { return WIDTH; }
	inline int getHeight() { return HEIGHT; }
	inline float getAspect() { return (float)WIDTH / (float)HEIGHT; }

private:
	SDL_Window *m_Window;
	SDL_GLContext m_Context;
	Input m_Input;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};