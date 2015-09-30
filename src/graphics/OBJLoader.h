#ifndef OBJLOADER_H
#define OBJLOADER_H

#include <string>
#include <vector>
#include <glm\glm.hpp>

struct Vertex {
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec2 TexCoords;
};

class OBJLoader
{
public:
	//static RawModel LoadObjModel(const std::string& fileName, Loader& loader);
private:
	static void ProcessVertices(char* vertexData, std::vector<int>& indices, std::vector<glm::vec2>& tempTextures,
		std::vector<glm::vec2>& textures, std::vector<glm::vec3>& tempNormals, std::vector<glm::vec3>& normals);
};

#endif // OBJLOADER_H