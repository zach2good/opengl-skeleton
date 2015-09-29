#pragma once

#include <algorithm> // std::copy

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <graphics\imgui\imgui.h>
#include <graphics\imgui\imgui_impl_sdl.h>

class DebugUi
{
public:
	DebugUi(SDL_Window* window);
	~DebugUi();

	void prepare();

	void processEvents(SDL_Event e);

	void render();

	SDL_Window* m_Window;
};
