#include "Scene3.h"

void Scene3::init()
{
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(true);
	m_Window->setGLBlend(true);

	camera.Position = vec3(0, 0, 10);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Position attribute
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	// TexCoord attribute
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glBindVertexArray(0); // Unbind VAO

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1.GetTextureID());
	glUniform1i(glGetUniformLocation(shader.GetId(), "ourTexture1"), 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2.GetTextureID());
	glUniform1i(glGetUniformLocation(shader.GetId(), "ourTexture2"), 1);
}

void Scene3::destroy()
{

}

void Scene3::update()
{
	shader.UpdateShader();
	trans.ChangeRotation(vec3(0.0f, 0.3f, 0.0f));
}

void Scene3::render()
{
	m_Window->clear();

	shader.Bind();

	shader.SetUniform4fv("model", trans.GetTransformationMatrix());
	shader.SetUniform4fv("view", camera.GetViewMatrix());
	shader.SetUniform4fv("projection", glm::perspective(camera.Zoom, m_Window->getAspect(), 0.1f, 1000.0f));
	shader.SetUniform3fv("viewPos", camera.Position);

	mesh->render();

	shader.Unbind();
}
