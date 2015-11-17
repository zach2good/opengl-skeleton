#include "Window2D.h"

Window::Window(const char* title, int width, int height)
	: TITLE(title), WIDTH(width), HEIGHT(height)
{
	init();
}

Window::~Window()
{
	cleanUp();
}

void Window::init()
{
	m_Window = SDL_CreateWindow(TITLE, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, HEIGHT, SDL_WINDOW_SHOWN);

	if (m_Window == NULL) 
	{ 
		printf(":(");
	}

	m_Renderer = SDL_CreateRenderer(m_Window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	if (m_Renderer == NULL) 
	{ 
		printf(":(");
	}

	m_Screen = SDL_CreateTexture(m_Renderer, SDL_GetWindowPixelFormat(m_Window), 0, WIDTH, HEIGHT);

	isRunning = true;
}

void Window::cleanUp()
{
	SDL_DestroyTexture(m_Screen);
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

void Window::update()
{
	SDL_RenderPresent(m_Renderer);
}

void Window::clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255);
	SDL_RenderClear(m_Renderer);
}

void Window::swap()
{
	SDL_GL_SwapWindow(m_Window);
}

void Window::drawPixel(int x, int y, int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, 255);
	SDL_RenderDrawPoint(m_Renderer, x, y);
}

bool Window::isCloseRequested()
{
	return !isRunning;
}

void Window::requestClose()
{
	isRunning = false;
}
