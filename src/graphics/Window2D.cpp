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
	Input& in = Input::instance();

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_MOUSEMOTION:
			in.handleEvent(event);
			break;
		case SDL_MOUSEBUTTONDOWN:
			in.handleEvent(event);
			break;
		case SDL_MOUSEBUTTONUP:
			in.handleEvent(event);
			break;
		case SDL_KEYUP:
			in.handleEvent(event);
			break;
		case SDL_KEYDOWN:
			in.handleEvent(event);

			switch (event.key.keysym.sym) {
			case SDLK_ESCAPE: requestClose(); break;
			default:
				break;
			}
			break;

		case SDL_QUIT:
			requestClose();
			break;
		default:
			break;
		}
	}

	startTime = Timer::GetTime();
}

void Window2D::clear()
{
	SDL_SetRenderDrawColor(m_Renderer, 0, 0, 0, 255);
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

void Window2D::drawLine(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, 255);
	SDL_RenderDrawLine(m_Renderer, x1, y1, x2, y2);
}

void Window2D::drawRect(int x1, int y1, int x2, int y2, int r, int g, int b)
{
	SDL_SetRenderDrawColor(m_Renderer, r, g, b, 255);

	auto rect = SDL_Rect();
	rect.x = x1;
	rect.y = y1;
	rect.w = x2 - x1;
	rect.h = y2 - y1;

	SDL_RenderDrawRect(m_Renderer, &rect);	
}

bool Window2D::isCloseRequested()
{
	return !isRunning;
}

void Window2D::requestClose()
{
	isRunning = false;
}
