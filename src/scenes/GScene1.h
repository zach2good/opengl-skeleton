#pragma once

#include <random>

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window.h"
#include "../graphics/DebugUi.h"
#include "../core/Input.h"

//#include "../graphics/ForwardRenderer.h"

#include "../graphics/ShaderProgram.h"
#include "../graphics/Camera.h"
#include "../graphics/GBuffer.h"
#include "../graphics/FrameBuffer.h"

#include "../core/GameObject.h"
#include "../graphics/Model.h"
#include "../components/Transform.h"

#include "../graphics/TextureLoader.h"

#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_sdl_gl3.h"

class GScene1
{
public:
	GScene1(Window* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:
	Window* m_Window;
	DebugUi* m_Debug;

	ShaderProgram shader_GeometryPass = ShaderProgram("../res/shaders/ssao_geometry");
	ShaderProgram shader_LightingPass = ShaderProgram("../res/shaders/ssao_lighting");
	ShaderProgram shader_SSAO = ShaderProgram("../res/shaders/ssao");
	ShaderProgram shader_SSAOBlur = ShaderProgram("../res/shaders/ssao_blur");
	ShaderProgram shader_Sobel = ShaderProgram("../res/shaders/sobel");

	Framebuffer frameBuffer = Framebuffer(m_Window->getWidth(), m_Window->getHeight());

	GLuint gBuffer;
	GLuint gPositionDepth, gNormal, gAlbedo;
	GLuint attachments[3] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2 };
	GLuint rboDepth;

	GLuint ssaoFBO, ssaoBlurFBO, finalFBO;
	GLuint ssaoColorBuffer, ssaoColorBufferBlur, finalColorBuffer;

	GLuint noiseTexture;

	std::default_random_engine generator;
	std::vector<glm::vec3> ssaoKernel;

	GLfloat lerp(GLfloat a, GLfloat b, GLfloat f)
	{
		return a + f * (b - a);
	}
	
	Camera camera;

	std::vector<GameObject*> objects;
	std::vector<glm::vec3> lights;

	glm::vec3 lightPos = glm::vec3(2.0, 4.0, 2.0);
	glm::vec3 lightColor = glm::vec3(1.0f);

	// Set up Model GameObject
	GameObject* sphere;

	// RenderQuad() Renders a 1x1 quad in NDC, best used for framebuffer color targets
	// and post-processing effects.
	GLuint quadVAO = 0;
	GLuint quadVBO;
	void RenderQuad()
	{
		if (quadVAO == 0)
		{
			GLfloat quadVertices[] = {
				// Positions        // Texture Coords
				-1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
				-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
				1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
				1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
			};
			// Setup plane VAO
			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)0);
			glEnableVertexAttribArray(1);
			glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (GLvoid*)(3 * sizeof(GLfloat)));
		}
		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glBindVertexArray(0);
	}
};
