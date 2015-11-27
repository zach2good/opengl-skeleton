#include "Input.h"

Input::Input()
{
}

Input::~Input()
{
}

Input& Input::instance()
{
	static Input instance;
	return instance;
}

void Input::handleEvent(const SDL_Event& event)
{
	if (event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		if (event.key.repeat) return;

		const bool isKeyDown = event.type == SDL_KEYDOWN;
		keyState[event.key.keysym.scancode] = isKeyDown;
		keyStateTimestamp[event.key.keysym.scancode] = SDL_GetTicks();
	}

	if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEBUTTONUP)
	{

	}
}

bool Input::isKeyDown(const SDL_Scancode code) const
{
	return keyState[code] > 0;
}

bool Input::isKeyUpdated(SDL_Scancode code, Uint32 timestamp) const
{
	return keyStateTimestamp[code] > timestamp;
}
