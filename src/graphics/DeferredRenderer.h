#pragma once

#include <vector>

#include "../common.h"
#include "../graphics/Window.h"
#include "../graphics/Camera.h"
#include "../graphics/ShaderProgram.h"

#include "../core/GameObject.h"

class DeferredRenderer
{
public:
	DeferredRenderer(Window* window);
	~DeferredRenderer();

	void submit(GameObject* go);
	void draw(ShaderProgram* shader, Camera* camera);

private:
	Window* m_Window;

	std::vector<GameObject*> m_gameObjects;
};