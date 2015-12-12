#pragma once

#include "../Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/ShaderProgram.h"

#define BUFFER_OFFSET(i) ((char *)NULL + (i))

class RBScene1
{
public:
	RBScene1(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;

	ShaderProgram shader = ShaderProgram("../res/shaders/rb/triangles");

	GLuint VBO, VAO, EBO;

	enum VAO_IDs { Triangles, NumVAOs };
	enum Buffer_IDs { ArrayBuffer, NumBuffers };
	enum Attrib_IDs { vPosition = 0 };

	GLuint VAOs[NumVAOs];
	GLuint Buffers[NumBuffers];

	const GLuint NumVertices = 12;

	GLfloat vertices[12] = {
		 -0.90f, -0.90f, // Triangle 1
		 0.85f, -0.90f,
		 -0.90f, 0.85f,
		 0.90f, -0.85f, // Triangle 2
		 0.90f, 0.90f,
		 -0.85f, 0.90f };
};