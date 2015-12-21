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
	shader_SSAO.Unbind();

	// Set up Camera
	camera.Position = vec3(4.5, 7, 25);

	// Set up Model GameObject
	GameObject* mainModel = new GameObject();
	mainModel->m_Model = new Model("../res/models/predator.obj");
	mainModel->m_Transform.SetPosition(vec3(0, 0, 0));
	mainModel->m_Transform.SetScale(vec3(0.10f));
	objects.push_back(mainModel);

	// Set up Wall GameObject
	GameObject* wallModel = new GameObject();
	wallModel->m_Model = new Model("../res/models/box.obj");
	wallModel->m_Transform.SetPosition(vec3(0, 0, -5));
	wallModel->m_Transform.SetScale(vec3(100, 100, 0.1));
	objects.push_back(wallModel);

	// Set up House GameObject
	GameObject* houseModel = new GameObject();
	houseModel->m_Model = new Model("../res/rungholt/house.obj");
	houseModel->m_Transform.SetPosition(vec3(15, 0, 0));
	houseModel->m_Transform.SetScale(vec3(0.05f));
	objects.push_back(houseModel);

	// Init GBuffer	
	glGenFramebuffers(1, &gBuffer);
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);

	// - Position + linear depth color buffer
	glGenTextures(1, &gPositionDepth);
	glBindTexture(GL_TEXTURE_2D, gPositionDepth);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGB, GL_FLOAT, NULL);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, gPositionDepth, 0);

	// - Normal color buffer
	glGenTextures(1, &gNormal);
	glBindTexture(GL_TEXTURE_2D, gNormal);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, gNormal, 0);

	// - Albedo color buffer
	glGenTextures(1, &gAlbedo);
	glBindTexture(GL_TEXTURE_2D, gAlbedo);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_Window->getWidth(), m_Window->getHeight(), 0, GL_RGBA, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, gAlbedo, 0);

	// - Tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	glDrawBuffers(3, attachments);

	// - Create and attach depth buffer (renderbuffer)
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, m_Window->getWidth(), m_Window->getHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);

	// - Finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
	{
		printf("GBuffer Framebuffer not complete!\n");
	}

	// Init SSAO Stage	
	glGenFramebuffers(1, &ssaoFBO);  glGenFramebuffers(1, &ssaoBlurFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);

	// - SSAO color buffer
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

	// - and blur stage
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
	std::uniform_real_distribution<GLfloat> randomFloats(0.0, 1.0); // generates random floats between 0.0 and 1.0
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

	glBindTexture(GL_TEXTURE_2D, 0);

	// Set up Debug vars
	m_Debug->addColor("Light Color", &lightColor);
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

	float ticks = ((float)SDL_GetTicks()) / 100.0f;
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
	shader_SSAO.Unbind();

	// 1. Geometry Pass: render scene's geometry/color data into gbuffer
	glBindFramebuffer(GL_FRAMEBUFFER, gBuffer);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glm::mat4 projection = glm::perspective(camera.Zoom, (GLfloat)m_Window->getAspect(), 0.1f, 1000.0f);
	glm::mat4 view = camera.GetViewMatrix();

	shader_GeometryPass.Bind();

	glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));
	glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "view"), 1, GL_FALSE, glm::value_ptr(view));

	for (GameObject* g : objects)
	{
		glUniformMatrix4fv(glGetUniformLocation(shader_GeometryPass.GetId(), "model"), 1, GL_FALSE, glm::value_ptr(g->m_Transform.GetTransformationMatrix()));
		glUniform1i(glGetUniformLocation(shader_GeometryPass.GetId(), "hasTextures"), g->m_Model->hasTextures());
		
		g->m_Model->draw(&shader_GeometryPass);
	}

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 2. Create SSAO texture
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoFBO);
	glClear(GL_COLOR_BUFFER_BIT);

	shader_SSAO.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, gPositionDepth);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, gNormal);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, noiseTexture);

	// Send kernel + rotation 
	for (GLuint i = 0; i < 64; ++i)
	{
		glUniform3fv(glGetUniformLocation(shader_SSAO.GetId(), ("samples[" + std::to_string(i) + "]").c_str()), 1, &ssaoKernel[i][0]);
	}

	glUniformMatrix4fv(glGetUniformLocation(shader_SSAO.GetId(), "projection"), 1, GL_FALSE, glm::value_ptr(projection));

	RenderQuad();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);


	// 3. Blur SSAO texture to remove noise
	glBindFramebuffer(GL_FRAMEBUFFER, ssaoBlurFBO);
	glClear(GL_COLOR_BUFFER_BIT);

	shader_SSAOBlur.Bind();

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, ssaoColorBuffer);

	RenderQuad();

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// 4. Lighting Pass: traditional deferred Blinn-Phong lighting now with added screen-space ambient occlusion
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

	lightPosView = glm::vec3(camera.GetViewMatrix() * glm::vec4(lightPos, 1.0));
	glUniform3fv(glGetUniformLocation(shader_LightingPass.GetId(), "light.Position"), 1, &lightPosView[0]);
	glUniform3fv(glGetUniformLocation(shader_LightingPass.GetId(), "light.Color"), 1, &lightColor[0]);

	glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), "light.Constant"), constant);
	glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), "light.Linear"), linear);
	glUniform1f(glGetUniformLocation(shader_LightingPass.GetId(), "light.Quadratic"), quadratic);

	glUniform1i(glGetUniformLocation(shader_LightingPass.GetId(), "draw_mode"), 1);

	RenderQuad();

	m_Debug->prepare();
	m_Debug->render();

	//ImGui_ImplSdlGL3_NewFrame();
	//ImGui::Text("Hello, world!");
	//ImGui::Render();
}
