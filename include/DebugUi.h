#pragma once

#include <algorithm> // std::copy

#include <SDL.h>

#include <glad\glad.h>

#include <imgui\imgui.h>
#include <imgui\imgui_impl_sdlogl3.h>

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
