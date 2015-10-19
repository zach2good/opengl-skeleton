#include "Input.h"

Input::Input()
{
	held_keys_ = map<SDL_Scancode, bool>();
	pressed_keys_ = map<SDL_Scancode, bool>();
	released_keys_ = map<SDL_Scancode, bool>();

	held_buttons_ = map<Uint8, bool>();
	pressed_buttons_ = map<Uint8, bool>();
	released_buttons_ = map<Uint8, bool>();
}

void Input::pollInput()
{
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_MOUSEMOTION:
			mouseMotion(e);
			break;
		case SDL_MOUSEBUTTONDOWN:
			mouseButtonDownEvent(e);
			break;
		case SDL_MOUSEBUTTONUP:
			mouseButtonUpEvent(e);
			break;
		case SDL_KEYDOWN:
			keyDownEvent(e);
			break;
		case SDL_KEYUP:
			keyUpEvent(e);
			break;
		case SDL_QUIT:
			//window.requestClose();
			break;
		default:
			break;
		}
	}
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