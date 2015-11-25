#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/ShaderProgram.h"


class Scene1
{
public:
	Scene1(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;

	ShaderProgram shader = ShaderProgram("../res/shaders/scene1");

	GLuint VBO, VAO, EBO;

	GLfloat vertices[12] = {
		0.5f,  0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f, 
		-0.5f,  0.5f, 0.0f  
	};

	GLuint indices[6] = { 
		0, 1, 3,
		1, 2, 3 
	};
};