#include "Window.h"

Window::Window(const char* title, int width, int height)
	: TITLE(title), WIDTH(width), HEIGHT(height), m_Input()
{
	init();
}

Window::~Window()
{
	cleanUp();
}

void Window::init()
{
	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Error");
	}

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 2);

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	// Start a Window
	m_Window = SDL_CreateWindow(TITLE,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!m_Window) {
		printf("Window Error");
	}

	// Start OpenGL Context
	m_Context = SDL_GL_CreateContext(m_Window);
	if (!m_Context) {
		printf("Context Error");
	}

	// Limit framerate to help screen tearing
	SDL_GL_SetSwapInterval(1);

#ifndef EMSCRIPTEN
	// Load GLAD
	if (!gladLoadGL()) {
		printf("GLAD Error");
	}
#endif

	// Print Info
	printf("GL_VERSION: %s \n", glGetString(GL_VERSION));
	printf("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
	printf("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));

	// Enable 3D
	glEnable(GL_DEPTH_TEST);

	glEnable(GL_MULTISAMPLE);

	// Face Culling
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	// Image Transparency
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	startTime = 0;
	endTime = 0;
	renderTime = 0;

	isRunning = true;
}

void Window::cleanUp()
{
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();
}

SDL_Window* Window::getWindow() const
{
	return m_Window;
}

SDL_GLContext Window::getContext()
{
	return m_Context;
}

void Window::update()
{
	m_Input.pollInput();
	if (m_Input.wasKeyPressed(SDL_SCANCODE_ESCAPE))
	{
		requestClose();
	}
}

void Window::clear()
{
	startTime = Timer::GetTime();
	glViewport(0, 0, WIDTH, HEIGHT);
	glClearColor(0.2, 0.2, 0.2, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swap()
{
	SDL_GL_SwapWindow(m_Window);
	endTime = Timer::GetTime();

	renderTime = endTime - startTime;

	const char* t = TITLE;

	SDL_SetWindowTitle(m_Window, std::to_string(1.0f / renderTime).c_str());
}

bool Window::isCloseRequested()
{
	return !isRunning;
}

void Window::requestClose()
{
	isRunning = false;
}
