#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <vector>
#include <map>
#include <string>

#include <SDL.h>

#ifdef EMSCRIPTEN
	#include <emscripten.h>
	#include <GL/glew.h>
	#include <GL/glut.h>

	// #include <GLES2/gl2.h> // GLES2
#else
	#include <glad/glad.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;





