#pragma once

#include "SDL.h"
#include <assert.h>
#include <array>

class Input 
{
public:
	static Input& instance();
	virtual ~Input();

	void handleEvent(const SDL_Event& event);

	bool isKeyDown(SDL_Scancode code) const;
	bool isKeyUpdated(SDL_Scancode code, Uint32 timestamp) const;	

private:
	// Singleton
	Input();

	std::array<bool, SDL_NUM_SCANCODES> keyState = std::array<bool, SDL_NUM_SCANCODES>{ false };
	std::array<Uint32, SDL_NUM_SCANCODES> keyStateTimestamp = std::array<Uint32, SDL_NUM_SCANCODES> { 0 };

	// NonCopyable
	Input(const Input& c);
	Input& operator=(const Input& c);
};