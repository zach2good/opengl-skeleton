#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <memory>
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

template<typename Creator, typename Destructor, typename... Arguments>
auto make_resource(Creator c, Destructor d, Arguments&&... args)
{
	auto r = c(std::forward<Arguments>(args)...);

	if (!r) 
	{ 
		throw std::system_error(errno, std::generic_category()); 
	}
	return std::unique_ptr<std::decay_t<decltype(*r)>, decltype(d)>(r, d);
}




