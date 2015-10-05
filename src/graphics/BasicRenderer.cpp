#include "BasicRenderer.h"

BasicRenderer::BasicRenderer()
	: shader(ShaderProgram("../src/shaders/basicShader"))
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
	entities.push_back(_e);
}

void BasicRenderer::Render(Camera camera)
{

	entities.clear();
}

void BasicRenderer::RenderSingle(Camera camera, Entity entity)
{
	//shader.Bind();

	//// Get Camera ViewMatrix
	//glm::mat4 view;
	//view = camera.GetViewMatrix();

	//// Get ProjectionMatrix
	//glm::mat4 projection;
	//projection = glm::perspective(camera.Zoom, (float)WIDTH / (float)HEIGHT, 0.1f, 1000.0f);

	//// Get ModelMatrix
	//glm::mat4 model;
	//model = entity.m_Transformation.GetTransformationMatrix();

	//// Get the uniform locations
	//GLint modelLoc = glGetUniformLocation(shader.GetId(), "model");
	//GLint viewLoc = glGetUniformLocation(shader.GetId(), "view");
	//GLint projLoc = glGetUniformLocation(shader.GetId(), "projection");

	//// Pass the matrices to the shader
	//glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));
	//glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(projection));
	//glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));

	////Render Entity
	//glBindVertexArray(entity.m_Mesh.VAO);

	//glEnableVertexAttribArray(0);
	//glEnableVertexAttribArray(1);
	//glEnableVertexAttribArray(2);

	//glDrawElements(GL_TRIANGLES, entity.m_Mesh.vertices.size(), GL_UNSIGNED_INT, 0);

	//glDisableVertexAttribArray(0);
	//glDisableVertexAttribArray(1);
	//glDisableVertexAttribArray(2);

	//glBindVertexArray(0);

	//shader.Unbind();
}