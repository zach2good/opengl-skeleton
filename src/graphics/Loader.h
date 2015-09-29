#pragma once

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <glm\glm.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <graphics\stb\stb_image.h>

#include <stdio.h>
#include <vector>
#include <string>
#include <iostream>

#include <graphics\models\RawModel.h>

class Loader
{
public:
	Loader();
	~Loader();

	RawModel loadToVAO(std::vector<glm::vec3> vertices, std::vector<glm::vec2> textures, std::vector<glm::vec3> normals, std::vector<int> indices);
	GLuint LoadTexture(const std::string& fileName, bool repeat = false);
	inline void UnbindVAO() { glBindVertexArray(0); }
private:
	std::vector<GLuint> m_vaos;
	std::vector<GLuint> m_vbos;
	std::vector<GLuint> m_textures;

	GLuint CreateVAO();
	void StoreDataInAttributeList(GLuint attribNumber, int attribSize, void* data, int dataSize);
	void BindIndicesBuffer(int* indices, int& count);
};
