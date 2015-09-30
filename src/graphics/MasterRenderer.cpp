
#include <glm\gtx\transform.hpp>
#include "MasterRenderer.h"

MasterRenderer::MasterRenderer(float aspectRatio)
	: m_projectionMatrix(glm::perspective(m_FOV, aspectRatio, m_NEAR_PLANE, m_FAR_PLANE)),
	m_entityRenderer(EntityRenderer(m_basicShader, m_projectionMatrix))
{
	// Don't draw faces we can't see
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	// Tell OpenGL to test for depth
	glEnable(GL_DEPTH_TEST);
	// Set clear color and clear the screen
	glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
	// Enable alpha blend
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	// Enable Antialiasing
	glEnable(GL_MULTISAMPLE);
}


MasterRenderer::~MasterRenderer()
{
}


void MasterRenderer::Render(Light& light, Camera camera)
{

}


void MasterRenderer::ProcessEntity(Entity& entity)
{
	// Get the textured model
	TexturedModel& texturedModel = entity.GetModel();
	// If the texturedmodel is in the map this will do nothing
	// If it is not in the map it will insert it
	m_entities.insert(tMap::value_type(texturedModel, std::vector<Entity>()));

	// Add the entity to the entities list
	m_entities[texturedModel].push_back(entity);
}