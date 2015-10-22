#pragma once

#include <cstdio>
#include <cstdlib>
#include <cstdint>

#include <vector>
#include <map>
#include <string>

#include <SDL.h>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
using namespace glm;

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#define WHITE vec3(1.0f)
#define RED vec3(1.0f, 0.0f, 0.0f)
#define BLUE vec3(0.0f, 0.0f, 1.0f)
#define GREEN vec3(0.0f, 1.0f, 0.0f)

#include "Window.h"
#include "DebugUi.h"
#include "Input.h"
#include "ShaderProgram.h"
#include "GBuffer.h"

#include "Material.h"
#include "DirLight.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "Camera.h"

#include "Quad.h"
#include "Mesh.h"

#include "Texture.h"

#include "Transformation.h"





