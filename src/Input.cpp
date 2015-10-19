#include "input.h"

Input::Input() :
	held_keys_(),
	pressed_keys_(),
	released_keys_(),

	held_buttons_(),
	pressed_buttons_(),
	released_buttons_()
{
	x = 0;
	y = 0;
}

void Input::beginNewFrame()
{
	pressed_keys_.clear();
	released_keys_.clear();

	pressed_buttons_.clear();
	released_buttons_.clear();
}

void Input::mouseMotion(const SDL_Event& event)
{
	int x = 0;
	int y = 0;

	SDL_GetMouseState(&x, &y);

	//int dx = x - centerX;
	//int dy = centerY - y;

	//camera.ProcessMouseMovement(dx, dy);
}

void Input::mouseButtonDownEvent(const SDL_Event& event)
{
	pressed_buttons_[event.button.button] = true;
	held_buttons_[event.button.button] = true;
}

void Input::mouseButtonUpEvent(const SDL_Event& event)
{
	released_buttons_[event.button.button] = true;
	held_buttons_[event.button.button] = false;
}

bool Input::wasMouseButtonPressed(Uint8 button)
{
	return pressed_buttons_[button];
}

bool Input::wasMouseButtonReleased(Uint8 button)
{
	return released_buttons_[button];
}

bool Input::isMouseButtonHeld(Uint8 button)
{
	return held_buttons_[button];
}

void Input::keyDownEvent(const SDL_Event& event)
{
    pressed_keys_[event.key.keysym.scancode] = true;
    held_keys_[event.key.keysym.scancode] = true;
}

void Input::keyUpEvent(const SDL_Event& event)
{
    released_keys_[event.key.keysym.scancode] = true;
    held_keys_[event.key.keysym.scancode] = false;
}

bool Input::wasKeyPressed(SDL_Scancode key)
{
    return pressed_keys_[key];
}

bool Input::wasKeyReleased(SDL_Scancode key)
{
    return released_keys_[key];
}

bool Input::isKeyHeld(SDL_Scancode key)
{
    return held_keys_[key];
}