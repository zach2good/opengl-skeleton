#pragma once

#include "SDL.h"
#include "glm\glm.hpp"
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

	bool isMouseDown(int code) const;

	glm::vec2 getPos();
	glm::vec2 getRelPos();

private:
	// Singleton
	Input();

	// Keys
	std::array<bool, SDL_NUM_SCANCODES> keyState = std::array<bool, SDL_NUM_SCANCODES>{ false };
	std::array<Uint32, SDL_NUM_SCANCODES> keyStateTimestamp = std::array<Uint32, SDL_NUM_SCANCODES> { 0 };

	// Mouse
	std::array<bool, 10> mouseState = std::array<bool, 10>{ false };
	std::array<Uint32, 10> mouseStateTimestamp = std::array<Uint32, 10> { 0 };

	// Mouse
	float mag = 0.010f;
	float x;
	float xrel;
	float y;
	float yrel;
	bool button1 = false;

	// NonCopyable
	Input(const Input& c);
	Input& operator=(const Input& c);
};