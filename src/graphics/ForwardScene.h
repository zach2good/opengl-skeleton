#pragma once

#include "Scene.h"

#include "../common.h"
#include "../core/Input.h"
#include "../core/Timer.h"
#include "../core/Util.h"

#include "Window.h"

#include "ShaderProgram.h"
#include "Camera.h"
#include "Entity.h"
#include "Mesh.h"
#include "Texture.h"

class ForwardScene
{
public:
	Texture* texture;

	ForwardScene(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

	Input input;
	Camera camera;

	glm::mat4 projection;

	std::vector<ShaderProgram*> shaders;
	std::vector<Entity*> entities;

private:
	Window* m_Window;
};