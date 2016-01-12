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

	Camera* m_Camera;

	std::vector<GameObject*> m_GameObjects;

	std::vector<PointLight*> m_PointLights;
	std::vector<DirectionalLight*> m_DirectionalLights;
	std::vector<SpotLight*> m_SpotLights;
};