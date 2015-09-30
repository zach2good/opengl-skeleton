#ifndef MASTERRENDERER_H
#define MASTERRENDERER_H

#include "EntityRenderer.h"
#include "entities\Camera.h"

class MasterRenderer
{
public:
	MasterRenderer(float aspectRatio);
	virtual ~MasterRenderer();

	void Render(Light& light, Camera camera);
	void ProcessEntity(Entity& entity);
private:
	const float m_FOV = 70;
	const float m_NEAR_PLANE = 0.1f;
	const float m_FAR_PLANE = 1000;
	glm::mat4 m_projectionMatrix;
	BasicShader m_basicShader;

	EntityRenderer m_entityRenderer;

	std::map<TexturedModel, std::vector<Entity>, tmCompare> m_entities;
};

#endif // MASTERRENDERER_H