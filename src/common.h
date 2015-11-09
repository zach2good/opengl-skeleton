#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <vector>
#include <map>
#include <string>

#include <SDL.h>

#ifndef EMSCRIPTEN
#include <glad/glad.h>
#endif

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;



#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "graphics/Color.h"

#include "graphics/Window.h"
#include "graphics/DebugUi.h"
#include "core/Input.h"
#include "core/Timer.h"

#include "graphics/ShaderProgram.h"
#include "graphics/BasicShader.h"

#include "graphics/DirLight.h"
#include "graphics/PointLight.h"
#include "graphics/SpotLight.h"
#include "graphics/Camera.h"
#include "graphics/Mesh.h"
#include "graphics/Texture.h"

#include "components/Transformation.h"





