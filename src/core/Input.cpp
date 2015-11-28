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
		const bool isButtonDown = event.type == SDL_MOUSEBUTTONDOWN;
		bool isLeft = event.button.button == SDL_BUTTON_LEFT;

		button1 = isLeft == isButtonDown;
	}

	if (event.type == SDL_MOUSEMOTION)
	{
		x = (float)event.motion.x;
		y = (float)event.motion.y;
		xrel = (float)event.motion.xrel * mag;
		yrel = (float)event.motion.yrel * mag;
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

bool Input::isMouseDown(int code) const
{
	return button1;
}

glm::vec2 Input::getPos()
{
	return glm::vec2(x, y);
}

glm::vec2 Input::getRelPos()
{
	return glm::vec2(xrel, yrel);
}

