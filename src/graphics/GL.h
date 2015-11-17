#pragma once

#ifdef EMSCRIPTEN
	#include <emscripten.h>
	#include <GL/glew.h>
	#include <GL/glut.h>
	//#include <GLES2/gl2.h> // GLES2
#elif  __APPLE__
	//#include "OpenGL/gl.h"
	//#include "OpenGL/glext.h"
	#include <glad/glad.h>
#else // Windows
	#include <glad/glad.h>
#endif
