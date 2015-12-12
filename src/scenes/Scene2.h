#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/Texture.h"

class Scene2
{
public:
	Scene2(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;

	ShaderProgram shader = ShaderProgram("../res/shaders/scene2");

	GLuint VBO, VAO, EBO;

	GLfloat vertices[36] = {
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, 
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, 
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, 
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  
	};

	GLuint indices[6] = { 
		0, 1, 3,
		1, 2, 3  
	};

	Texture	texture1 = Texture("../res/textures/container.jpg");
	Texture	texture2 = Texture("../res/textures/awesomeface.png");
};