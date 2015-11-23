#pragma once

#include "SDL.h"
#include "glm/glm.hpp"
using namespace glm;

#include <map>

class Input 
{
public:
	Input();

	void pollInput();

	void mouseButtonDownEvent(const SDL_Event& event);
	void mouseButtonUpEvent(const SDL_Event& event);

	bool wasMouseButtonPressed(Uint8 button);
	bool wasMouseButtonReleased(Uint8 button);
	bool isMouseButtonHeld(Uint8 button);

    void keyDownEvent(const SDL_Event& event);
    void keyUpEvent(const SDL_Event& event);

    bool wasKeyPressed(SDL_Scancode key);
    bool wasKeyReleased(SDL_Scancode key);
    bool isKeyHeld(SDL_Scancode key);

	inline void SetMouseX(int value) { m_MouseX = value; }
	inline void SetMouseY(int value) { m_MouseY = value; }

	void SetCursor(bool value) const;
	void SetMousePosition(const vec2& pos);
	inline vec2 GetMousePosition() const { return vec2((float)m_MouseX, (float)m_MouseY); }

	bool requestQuit;

private:
	void beginNewFrame();

	SDL_Event e;

	

	int m_MouseX;
	int m_MouseY;

	std::map<Uint8, bool> held_buttons_;
	std::map<Uint8, bool> pressed_buttons_;
	std::map<Uint8, bool> released_buttons_;

    std::map<SDL_Scancode, bool> held_keys_;
    std::map<SDL_Scancode, bool> pressed_keys_;
    std::map<SDL_Scancode, bool> released_keys_;
};