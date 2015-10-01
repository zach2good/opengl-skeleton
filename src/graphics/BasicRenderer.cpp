#include "BasicRenderer.h"

BasicRenderer::BasicRenderer()
{
}

BasicRenderer::~BasicRenderer()
{

}

void BasicRenderer::Prepare()
{
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
}

void BasicRenderer::Submit(Entity _e)
{
	entity = _e;
}

void BasicRenderer::Render(Camera camera)
{
	shader.Bind();

	// Bind Textures using texture units
	// 1
	glActiveTexture(GL_TEXTURE0);
	entity.m_Mesh.textures.at(0).BindTexture();
	glUniform1i(glGetUniformLocation(shader.GetId(), "texture"), 0);

	// Create camera transformation
	glm::mat4 view;
	view = camera.GetViewMatrix();
	glm::mat4 projection;

	projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

	// Get the uniform locations
	GLint modelLoc = glGetUniformLocation(shader.GetId(), "model");
	GLint viewLoc = glGetUniformLocation(shader.GetId(), "view");
	GLint projLoc = glGetUniformLocation(shader.GetId(), "projection");

	// Pass the matrices to the shader
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));

	//Render Entity
	glBindVertexArray(entity.m_Mesh.VBO);

	glm::mat4 model;
	glm::vec3 pos = entity.m_Transformation.GetPosition();
	glm::vec3 rot = entity.m_Transformation.GetRotation();
	glm::vec3 sca = entity.m_Transformation.GetScale();
	model = Maths::CreateTransformMatrix(pos, rot, sca);
	glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glDrawElements(GL_TRIANGLES, entity.m_Mesh.vertices.size(), GL_UNSIGNED_INT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);

	glBindVertexArray(0);

	shader.Unbind();
}