#pragma once

#ifdef EMSCRIPTEN
	#include <emscripten.h>
	#include <GL/glew.h>
	#include <GL/glut.h>
#else
	#include <glad/glad.h>
#endif