#include "common.h"

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);
	DebugUi debugUi = DebugUi(window.getWindow());

	Camera camera = Camera();
	camera.Position = vec3(0, 0, 5);

	ShaderProgram basicShader = ShaderProgram("../res/shaders/basicShader");
	ShaderProgram lampShader = ShaderProgram("../res/shaders/lampShader");

	Mesh objectMesh = Mesh("../res/models/head/head.obj");
	Mesh lightMesh = Mesh("../res/models/cube.obj");

	Texture texture = Texture("../res/models/container.png");

	Transformation objectTrans = Transformation();
	objectTrans.SetScale(vec3(5.8f));

	Transformation lightTrans = Transformation();
	lightTrans.SetPosition(vec3(1, 1, 1));
	lightTrans.SetScale(vec3(0.2f));


	bool wireframe = false;
	while (!window.isCloseRequested()) {

		// Determine deltaTime
		float deltaTime = 1000.0f / SDL_GetTicks();

		// Poll inputs
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				window.requestClose();
			}
			if (e.key.keysym.sym == SDLK_PERIOD) {
				wireframe = true;
			}
			if (e.key.keysym.sym == SDLK_COMMA) {
				wireframe = false;
			}
			if (e.key.keysym.sym == SDLK_r) {
				objectTrans.ChangeRotation(glm::vec3(0, glm::radians(100.0f), 0));
			}
			if (e.key.keysym.sym == SDLK_t) {
				objectTrans.ChangeRotation(glm::vec3(0, glm::radians(-100.0f), 0));
			}
			if (e.key.keysym.sym == SDLK_a) {
				camera.ProcessKeyboard(LEFT, deltaTime);
			}
			if (e.key.keysym.sym == SDLK_d) {
				camera.ProcessKeyboard(RIGHT, deltaTime);
			}
			if (e.key.keysym.sym == SDLK_w) {
				camera.ProcessKeyboard(FORWARD, deltaTime);
			}
			if (e.key.keysym.sym == SDLK_s) {
				camera.ProcessKeyboard(BACKWARD, deltaTime);
			}
			if (e.key.keysym.sym == SDLK_q) {
				camera.ProcessKeyboard(UP, deltaTime);
			}
			if (e.key.keysym.sym == SDLK_e) {
				camera.ProcessKeyboard(DOWN, deltaTime);
			}
		}

		glPolygonMode(GL_FRONT_AND_BACK, (wireframe) ? GL_LINE : GL_FILL);

		//Update
		float time_sin = sinf(SDL_GetTicks() / 500.0f);
		float time_cos = cosf(SDL_GetTicks() / 500.0f);
		objectTrans.SetRotation(vec3(0, time_sin * 10, 0));
		lightTrans.SetPosition(vec3(time_sin * 2, 0, time_cos * 2));

		// Clear
		window.clear();

		// 3D Render
		basicShader.Bind();

		basicShader.SetUniform4fv("model", objectTrans.GetTransformationMatrix());
		basicShader.SetUniform4fv("view", camera.GetViewMatrix());
		basicShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));

		basicShader.SetUniform3fv("viewPos", camera.Position);

		glUniform1i(glGetUniformLocation(basicShader.GetId(), "material.diffuse"), 0);
		texture.Bind(0);

		basicShader.SetUniform3fv("material.specular", vec3(0.5f));
		basicShader.SetUniformf("material.shininess", 32.0f);

		basicShader.SetUniform3fv("light.position", lightTrans.GetPosition());

		basicShader.SetUniform3fv("light.ambient", vec3(1, 1, 1));
		basicShader.SetUniform3fv("light.diffuse", vec3(1, 1, 1));
		basicShader.SetUniform3fv("light.specular", vec3(1, 1, 1));
		objectMesh.render();
		basicShader.Unbind();

		// Draw White Light
		lampShader.Bind();
		lampShader.SetUniform4fv("model", lightTrans.GetTransformationMatrix());
		lampShader.SetUniform4fv("view", camera.GetViewMatrix());
		lampShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));
		lightMesh.render();
		lampShader.Unbind();

		// 2D Render
#ifdef _DEBUG 
		// Render 2D
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		debugUi.prepare();
		debugUi.render();
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINES); }
#endif // _DEBUG 

		// Swap
		window.swap();
	}

	debugUi.cleanUp();
	window.cleanUp();

	return EXIT_SUCCESS;
}