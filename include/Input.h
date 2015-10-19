#pragma once
#include "common.h"

class Input 
{
public:
    Input();

	void pollInput();

    void beginNewFrame();

	void mouseMotion(const SDL_Event& event);

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

private:

	SDL_Event e;

	int x;
	int y;

	std::map<Uint8, bool> held_buttons_;
	std::map<Uint8, bool> pressed_buttons_;
	std::map<Uint8, bool> released_buttons_;

    std::map<SDL_Scancode, bool> held_keys_;
    std::map<SDL_Scancode, bool> pressed_keys_;
    std::map<SDL_Scancode, bool> released_keys_;
};