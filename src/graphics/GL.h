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
#else
	#include <glad/glad.h>
#endif

static class GL
{
protected:
	inline static void init()
	{
		#ifdef EMSCRIPTEN

		#elif  __APPLE__

		#else

		#endif
	}

public:
private:
};

