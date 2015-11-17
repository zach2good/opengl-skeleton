#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>

#include <SDL.h>
#include <glad/glad.h>


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

	void drawPixel(int x, int y, int r, int g, int b);

	bool isCloseRequested();
	void requestClose();

	int getWidth() const { return WIDTH; }
	int getHeight() const { return HEIGHT; }
	float getAspect() const	{ return float(WIDTH) / float(HEIGHT); }

private:
	SDL_Window *m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Screen;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};