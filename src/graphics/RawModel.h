#pragma once

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

class RawModel
{
public:
	RawModel(GLuint _vaoID, int _vertexCount);
	~RawModel();

	GLuint getVaoID();
	int getVertexCount();

private:
	 GLuint vaoID;
	 int vertexCount;
};
