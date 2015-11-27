#include "Input.h"

Input::Input() :
	state{false},
	stateTimestamp{0}
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
	assert(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP);
	if (event.key.repeat) return;

	const bool isKeyDown = event.type == SDL_KEYDOWN;
	state[event.key.keysym.scancode] = isKeyDown;
	stateTimestamp[event.key.keysym.scancode] = SDL_GetTicks();
}

bool Input::isDown(const SDL_Scancode code) const
{
	return state[code] > 0;
}

bool Input::isUpdated(SDL_Scancode code, Uint32 timestamp) const
{
	return stateTimestamp[code] > timestamp;
}
