#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/ShaderProgram.h"
#include "../graphics/Texture.h"
#include "../graphics/Camera.h"
#include "../graphics/Mesh.h"
#include "../graphics/FrameBuffer.h"
#include "../components/Transformation.h"

class Scene5
{
public:
	Scene5(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;
	ShaderProgram shader = ShaderProgram("../res/shaders/scene5");
	ShaderProgram depthShader = ShaderProgram("../res/shaders/depth");
	Camera camera;
	Texture	texture = Texture("../res/textures/box.jpg");
	Mesh* mesh = new Mesh("../res/models/box.obj");

	Transformation trans;
	Transformation light;

	Framebuffer frameBuffer = Framebuffer(m_Window->getWidth(), m_Window->getHeight());
};
