#pragma once

#include "../common.h"

#include "../core/Input.h"

#include "../core/Timer.h"

class Window2D
{
public:
	Window2D(const char* title, int width, int height);
	~Window2D();

	void init();
	void cleanUp();

	SDL_Window* Window2D::getWindow() const;

	void update();
	void clear();
	void swap();

	void drawPixel(int x, int y, int r, int g, int b);
	void drawLine(int x1, int y1, int x2, int y2, int r, int g, int b);
	void drawRect(int x1, int y1, int x2, int y2, int r, int g, int b);

	bool isCloseRequested();
	void requestClose();

	int getWidth() const { return WIDTH; }
	int getHeight() const { return HEIGHT; }
	float getAspect() const	{ return float(WIDTH) / float(HEIGHT); }

private:
	SDL_Window *m_Window;
	SDL_Renderer* m_Renderer;
	SDL_Texture* m_Screen;

	SDL_Event event;

	double startTime;
	double endTime;
	double renderTime;

	int fpsAccumulator;

	const char* TITLE;
	int HEIGHT;
	int WIDTH;

	bool isRunning;
};