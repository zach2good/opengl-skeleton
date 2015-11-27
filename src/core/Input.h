#pragma once

#include "SDL.h"
#include "glm/glm.hpp"
using namespace glm;

#include <array>

class Input 
{
public:
	static Input& instance();
	virtual ~Input();

	void handleEvent(const SDL_Event& event);

	bool isDown(SDL_Scancode code) const;
	bool isUpdated(SDL_Scancode code, Uint32 timestamp) const;	

private:
	// Singleton
	Input();

	std::array<bool, SDL_NUM_SCANCODES> state;
	std::array<Uint32, SDL_NUM_SCANCODES> stateTimestamp;

	// NonCopyable
	Input(const Input& c);
	Input& operator=(const Input& c);
};