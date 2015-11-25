#include "ForwardScene.h"

void ForwardScene::init()
{
	m_Window->setGLCullFace(false);
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);

	input = Input();
	camera = Camera(vec3(0.0f, 0.0f, 5.0f));
	projection = glm::perspective(45.0f, (GLfloat)m_Window->getAspect(), 0.1f, 100.0f);
	shaders.push_back(new ShaderProgram("../res/shaders/forward"));
	entities.push_back(new Entity(new Mesh("../res/models/box.obj")));

	texture = new Texture("../res/textures/box.jpg");
}

void ForwardScene::destroy()
{
	for each (ShaderProgram* sh in shaders)
	{
		delete sh;
	}

	for each (Entity* e in entities)
	{
		delete e;
	}
}

void ForwardScene::update()
{
	// Input handling

	// Updates
	entities.at(0)->trans.ChangeRotation(vec3(0.0f, 1.0f, 0.0f));
}

void ForwardScene::render()
{
	texture->Bind(0);

	shaders.at(0)->Bind();

	for each (Entity* e in entities)
	{
		shaders.at(0)->SetUniform4fv("model", e->trans.GetTransformationMatrix());
		shaders.at(0)->SetUniform4fv("view", camera.GetViewMatrix());
		shaders.at(0)->SetUniform3fv("viewPos", camera.Position);
		shaders.at(0)->SetUniform4fv("projection", projection);

		shaders.at(0)->SetUniform1i("texture_0", 0);

		e->mesh->render();
	}

	shaders.at(0)->Unbind();
}
