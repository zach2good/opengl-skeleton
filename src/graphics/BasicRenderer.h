#pragma once

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <stdio.h>

#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <utils\Maths.h>

#include <entities\Entity.h>
#include <entities\Camera.h>
#include <graphics\shaders\ShaderProgram.h>

class BasicRenderer
{
public:
	BasicRenderer();
	~BasicRenderer();

	void Prepare();
	void Submit(Entity entity);
	void Render(Camera camera);

private:
	ShaderProgram shader;
	Entity entity;
	std::vector<Entity> entities;
	int WIDTH;
	int HEIGHT;

	void RenderSingle(Camera camera, Entity entity);
};
