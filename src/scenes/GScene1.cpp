#include "GScene1.h"

void GScene1::init()
{
	// Set up Window + OpenGL
	m_Window->setGLDepthTest(true);
	m_Window->setGLMultisample(true);
	m_Window->setGLCullFace(true);
	m_Window->setGLBlend(true);

	m_Debug = new DebugUi(m_Window->getWindow());

	// Set up Shaders
	shader_LightingPass.Bind();
	glUniform1i(shader_LightingPass.GetUniformLocation("gPositionDepth"), 0);
	glUniform1i(shader_LightingPass.GetUniformLocation("gNormal"), 1);
	glUniform1i(shader_LightingPass.GetUniformLocation("gAlbedo"), 2);
	glUniform1i(shader_LightingPass.GetUniformLocation("ssao"), 3);
	shader_LightingPass.Unbind();

	shader_SSAO.Bind();
	glUniform1i(shader_SSAO.GetUniformLocation("gPositionDepth"), 0);
	glUniform1i(shader_SSAO.GetUniformLocation("gNormal"), 1);
	glUniform1i(shader_SSAO.GetUniformLocation("texNoise"), 2);

	glUniform1i(shader_SSAO.GetUniformLocation("kernelSize"), kernelSize);
	glUniform1f(shader_SSAO.GetUniformLocation("radius"), radius);
	shader_SSAO.Unbind();

	shader_SSAOBlur.Bind();
	glUniform1i(shader_SSAO.GetUniformLocation("blurSize"), blurSize);
	shader_SSAOBlur.Unbind();

	// Set up Camera
	camera.Position = vec3(4.5, 7, 25);

	// Set up Model GameObject
	GameObject* mainModel = new GameObject("Chocobo");
	mainModel->m_Model = new Model("../res/models/Chocobo/chocobo.obj");
	mainModel->m_Transform.m_position = (vec3(-10, 0, 0));
	mainModel->m_Transform.m_rotation = (vec3(0, 0, 180));
	mainModel->m_Transform.m_scale = (vec3(0.05f));
	objects.push_back(mainModel);

	// Set up Model GameObject
	GameObject* mainModel2 = new GameObject("Mandragora");
	mainModel2->m_Model = new Model("../res/models/Mandragora/0075_player50out.dae");
	mainModel2->m_Transform.m_position = (vec3(0, 0, 0));
	mainModel2->m_Transform.m_rotation = (vec3(0, 0, 180));
	mainModel2->m_Transform.m_scale = (vec3(0.05f));
	objects.push_back(mainModel2);

	// Set up Model GameObject
	GameObject* mainModel3 = new GameObject("Vivi");
	mainModel3->m_Model = new Model("../res/models/Vivi/0044_player05out.dae");
	mainModel3->m_Transform.m_position = (vec3(10, 0, 0));
	mainModel3->m_Transform.m_rotation = (vec3(0, 0, 180));
	mainModel3->m_Transform.m_scale = (vec3(0.05f));
	objects.push_back(mainModel3);

	// Set up Wall GameObject
	GameObject* floorModel = new GameObject("Floor");
	floorModel->m_Model = new Model("../res/models/box.obj");
	floorModel->m_Transform.m_position = (vec3(0, 0, 0));
	floorModel->m_Transform.m_scale = (vec3(100, 0.1, 100));
	objects.push_back(floorModel);

	// Lights
	GameObject* light1 = new GameObject("Light 1");
	light1->isLight = true;
	light1->m_Transform.m_position = (vec3(10, 2, 0));
	objects.push_back(light1);

	GameObject* light2 = new GameObject("Light 2");
	light2->isLight = true;
	light2->m_Transform.m_position = (vec3(-10, 2, 0));
	objects.push_back(light2);

	// Init GBuffer	
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	// Position + Depth
	glGenTextures(1, &gPositionDepth);
	glBindTexture(GL_TEXTURE_2D, gPositionDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPositionDepth, 0);

	// Normals
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	// Albedo
	glGenTextures(1, &gAlbedo);
	glBindTexture(GL_TEXTURE_2D, gAlbedo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);

	// Attach
	glDrawBuffers(3, attachments);

	// Depth Buffer
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Window->getWidth(), m_Window->getHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("GBuffer Framebuffer not complete!\n");
	}

	// Init SSAO Stage	
	glGenFramebuffers(1, &ssaoFBO);  glGenFramebuffers(1, &ssaoBlurFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);

	glGenTextures(1, &ssaoColorBuffer);
	glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBuffer, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("SSAO Framebuffer not complete!\n");
	}

	// Init Blur Stage
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);

	glGenTextures(1, &ssaoColorBufferBlur);
	glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, ssaoColorBufferBlur, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("SSAO Blur Framebuffer not complete!\n");
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Sample kernel
	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0);
	for (GLuint i = 0; i < 64; ++i)
	{
		glm::vec3 sample(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, randomFloats(generator));
		sample = glm::normalize(sample);
		sample *= randomFloats(generator);
		GLfloat scale = GLfloat(i) / 64.0;

		// Scale samples s.t. they're more aligned to center of kernel
		scale = lerp(0.1f, 1.0f, scale * scale);
		sample *= scale;
		ssaoKernel.push_back(sample);
	}

	// Noise texture
	std::vector<glm::vec3> ssaoNoise;
	for (GLuint i = 0; i < 16; i++)
	{
		glm::vec3 noise(randomFloats(generator) * 2.0 - 1.0, randomFloats(generator) * 2.0 - 1.0, 0.0f); // rotate around z-axis (in tangent space)
		ssaoNoise.push_back(noise);
	}

	glGenTextures(1, &noiseTexture);

	glBindTexture(GL_TEXTURE_2D, noiseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, 4, 4, 0, GL_RGB, GL_FLOAT, &ssaoNoise[0]);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Set up Debug vars
	m_Debug->addRenderingWidget(&draw_mode);
	m_Debug->addGOVector(&objects);

	m_Debug->addBool("Texture Maps", &useTextures);
	m_Debug->addBool("Normal Maps", &useNormalMaps);
	m_Debug->addBool("Specular Maps", &useSpecularMaps);

	m_Debug->addFloat("SSAO Radius", &radius, 1, 50);
	m_Debug->addInt("SSAO Kernel Size", &kernelSize, 1, 128);

	m_Debug->addInt("Blur Size", &blurSize, 1, 20);

	m_Debug->addColor("Light Color", &lightColor);
	m_Debug->addVec3("Light Position", &lightPos);
	m_Debug->addFloat("Ambient Light Amount", &ambientLevel, 0, 1);
}

void GScene1::destroy()
{

}

void GScene1::update()
{
	shader_GeometryPass.UpdateShader();
	shader_LightingPass.UpdateShader();
	shader_SSAO.UpdateShader();
	shader_SSAOBlur.UpdateShader();

	Input& input = Input::instance();

	float speed = 0.1f;

	if (input.isKeyDown(SDL_SCANCODE_A)) {
		camera.ProcessKeyboard(LEFT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_D)) {
		camera.ProcessKeyboard(RIGHT, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_W)) {
		camera.ProcessKeyboard(FORWARD, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_S)) {
		camera.ProcessKeyboard(BACKWARD, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_E)) {
		camera.ProcessKeyboard(UP, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_Q)) {
		camera.ProcessKeyboard(DOWN, speed);
	}

	if (input.isKeyDown(SDL_SCANCODE_SPACE)) {
		lightPos = camera.Position;
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
		camera.ProcessMouseMovement(input.getRelPos().x * 10.0f, -input.getRelPos().y * 10.0f);
	}

	ticks += m_Window->getDelta() * 10.0f;

	objects.at(0)->m_Transform.m_position.x += 2.0f * direction * m_Window->getDelta();

	if (objects.at(0)->m_Transform.m_position.x > -10)
	{
		direction = -1;
	}

	if (objects.at(0)->m_Transform.m_position.x < -30)
	{
		direction = 1;
	}

	objects.at(1)->m_Transform.m_position.z = -5 + sinf(ticks);
	objects.at(1)->m_Transform.m_position.x = cosf(ticks);



	objects.at(2)->m_Transform.m_rotation.y = 2 * ticks;

}

void GScene1::render()
{
	// Set up Shaders
	shader_LightingPass.Bind();
	glUniform1i(shader_LightingPass.GetUniformLocation("gPositionDepth"), 0);
	glUniform1i(shader_LightingPass.GetUniformLocation("gNormal"), 1);
	glUniform1i(shader_LightingPass.GetUniformLocation("gAlbedo"), 2);
	glUniform1i(shader_LightingPass.GetUniformLocation("ssao"), 3);
	shader_LightingPass.Unbind();

	shader_SSAO.Bind();
	glUniform1i(shader_SSAO.GetUniformLocation("gPositionDepth"), 0);
	glUniform1i(shader_SSAO.GetUniformLocation("gNormal"), 1);
	glUniform1i(shader_SSAO.GetUniformLocation("texNoise"), 2);

	glUniform1i(shader_SSAO.GetUniformLocation("kernelSize"), kernelSize);
	glUniform1f(shader_SSAO.GetUniformLocation("radius"), radius);
	shader_SSAO.Unbind();

	shader_SSAOBlur.Bind();
	glUniform1i(shader_SSAO.GetUniformLocation("blurSize"), blurSize);
	shader_SSAOBlur.Unbind();

	// Geometry Pass
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)m_Window->getAspect(), 0.1f, 1000.0f);
	glm::mat4 view = camera.GetViewMatrix();

	shader_GeometryPass.Bind();

	glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	lights.clear();
	for (GameObject* g : objects)
	{
		if (g->m_Model)
		{
			glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "model"), 1, GL_FALSE, glm::value_ptr(g->m_Transform.GetTransformationMatrix()));

			glUniform1i(glGetUniformLocation(shader_GeometryPass.GetId(), "useTextures"), g->m_Model->hasTextures && useTextures);
			glUniform1i(glGetUniformLocation(shader_GeometryPass.GetId(), "useNormalMaps"), g->m_Model->hasNormalMaps && useNormalMaps);
			glUniform1i(glGetUniformLocation(shader_GeometryPass.GetId(), "useSpecularMaps"), g->m_Model->hasSpecularMaps && useSpecularMaps);

			g->m_Model->draw(&shader_GeometryPass);
		}

		if (g->isLight)
		{
			lights.push_back(g);
		}
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// SSAO Pass
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
	glClear(GL_COLOR_BUFFER_BIT);

	shader_SSAO.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPositionDepth);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);

	for (GLuint i = 0; i < 64; ++i)
	{
		glUniform3fv(glGetUniformLocation(shader_SSAO.GetId(), ("samples[" + std::to_string(i) + "]").c_str()), 1, &ssaoKernel[i][0]);
	}

	glUniformMatrix4fv(glGetUniformLocation(shader_SSAO.GetId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	RenderQuad();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Blur SSAO Pass
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
	glClear(GL_COLOR_BUFFER_BIT);

	shader_SSAOBlur.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);

	RenderQuad();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// Lighting Pass
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	shader_LightingPass.Bind();

	const GLfloat constant = 1.0;
	const GLfloat linear = 0.09;
	const GLfloat quadratic = 0.032;

	glm::vec3 lightPosView;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPositionDepth);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, gAlbedo);

	glActiveTexture(GL_TEXTURE3);
	glBindTexture(GL_TEXTURE_2D, ssaoColorBufferBlur);

	glUniform1i(glGetUniformLocation(shader_LightingPass.GetId(), "draw_mode"), draw_mode);
	glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), "ambientLevel"), ambientLevel);

	for (int i = 0; i < lights.size(); i++)
	{
		int lightType = 0; // lights.at(i)-> Type?

		switch (lightType)
		{
		case 0: // Point
			break;

		case 1:	// Directional
			break;

		case 2:	// Spot
			break;

		}
		glUniform1i(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Type").c_str()), lightType);

		lightPosView = glm::vec3(camera.GetViewMatrix() * glm::vec4(lights.at(i)->m_Transform.m_position, 1.0));
		glUniform3fv(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Position").c_str()), 1, &lightPosView[0]);
		glUniform3fv(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Color").c_str()), 1, &lightColor[0]);

		glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Constant").c_str()), constant);
		glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Linear").c_str()), linear);
		glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Quadratic").c_str()), quadratic);

		// Spotlight Only
		glUniform3fv(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].Direction").c_str()), 1, &lightColor[0]);
		glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].CutOff").c_str()), constant);
		glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), ("lights[" + std::to_string(i) + "].OuterCutOff").c_str()), constant);
	}

	RenderQuad();

	// Debug overlay
	m_Debug->prepare();
	m_Debug->render();
}
