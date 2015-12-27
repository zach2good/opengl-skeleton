#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <iomanip>
#include <map>

#include <SDL.h>

#ifdef EMSCRIPTEN
	#include <emscripten.h>
	#include <GL/glew.h>
	#include <GL/glut.h>
#else
	#include <glad/glad.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <assimp/scene.h>
#include <assimp/mesh.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>

#include <../core/Util.h>







