#pragma once

#include <string>
#include <stdio.h>
#include <time.h>
#include <vector>

#include <glm\glm.hpp>

#include <graphics\models\Mesh.h>
#include <graphics\textures\Texture.h>

class OBJLoader
{
public:
	static Mesh LoadFromFile(const char* fileName, const char* texFileName);
private:
	static void ProcessVertices(char* vertexData, std::vector<GLuint>& indices, std::vector<glm::vec2>& tempTextures,
		std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals);
};
