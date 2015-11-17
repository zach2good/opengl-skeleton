#pragma once

#include <algorithm> // std::copy

#include "../common.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"

#ifdef EMSCRIPTEN
#include "../imgui/imgui_impl_sdlems.h"
#else
#include "../imgui/imgui_impl_sdl_gl3.h"
#endif

struct FloatDebug
{
	FloatDebug(const char* title, float* value, float min, float max) :
		title(title), value(value), min(min), max(max) {}

	const char* title;
	float* value;
	float min;
	float max;
};

struct BoolDebug
{
	BoolDebug(const char* title, bool* value) :
		title(title), value(value) {}

	const char* title;
	bool* value;
};

struct ColorDebug
{
	ColorDebug(const char* title, vec3* col) :
		title(title), col(col) {}

	const char* title;
	vec3* col;
};

struct Vec3Debug
{
	Vec3Debug(const char* title, vec3* val) :
		title(title), val(val) {}

	const char* title;
	vec3* val;
};

class DebugUi
{
public:
	explicit DebugUi(SDL_Window* window);
	~DebugUi();

	void prepare();
	void cleanUp();

	void processEvents(SDL_Event e);

	void render();

	void addFloat(const char* title, float* var);
	void addFloat(const char* title, float* var, float min, float max);

	void addBool(const char* title, bool* var);

	void addColor(const char* title, vec3* val);

	void addVec3(const char* title, vec3* val);

	std::vector<FloatDebug> floats;
	std::vector<BoolDebug> bools;
	std::vector<ColorDebug> colors;
	std::vector<Vec3Debug> vecs;

	SDL_Window* m_Window;

	bool ColorPicker(const char* label, ImColor* color);
};
