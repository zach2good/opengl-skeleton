#include "Window2D.h"

Window2D::Window2D(const char* title, int width, int height)
	: TITLE(title), WIDTH(width), HEIGHT(height)
{
	init();
}

Window2D::~Window2D()
{
	cleanUp();
}

void Window2D::init()
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

	startTime = 0;
	endTime = 0;
	renderTime = 0;
	fpsAccumulator = 0;

	isRunning = true;
}

void Window2D::cleanUp()
{
	SDL_DestroyTexture(m_Screen);
	SDL_DestroyRenderer(m_Renderer);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

SDL_Window* Window2D::getWindow() const
{
	return m_Window;
}

void Window2D::update()
{
	startTime = Timer::GetTime();
}

void Window2D::clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 100, 100, 100, 255);
	SDL_RenderClear(m_Renderer);
}

void Window2D::swap()
{
	SDL_RenderPresent(m_Renderer);	

	endTime = Timer::GetTime();
	renderTime = endTime - startTime;

	fpsAccumulator += (int)(renderTime * 1000.0f);

	std::string t = TITLE;
	std::string fpsString = std::to_string(1.0f / renderTime);
	fpsString.resize(4);
	std::string titleString = t + " " + fpsString + "FPS";

	if (std::isgreater(fpsAccumulator, 1000))
	{
		SDL_SetWindowTitle(m_Window, titleString.c_str());
		fpsAccumulator = 0;
	}
}

void Window2D::drawPixel(int x, int y, int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, 255);
	SDL_RenderDrawPoint(m_Renderer, x, y);
}

bool Window2D::isCloseRequested()
{
	return !isRunning;
}

void Window2D::requestClose()
{
	isRunning = false;
}
