#include "common.h"

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);
	DebugUi debugUi = DebugUi(window.getWindow());
	Camera camera = Camera();
	camera.Position = vec3(0, -0.2f, 2.5f);

	ShaderProgram shader = ShaderProgram("../res/shaders/basicShader");

	Mesh mesh = Mesh("../res/models/head/head.obj");
	Texture texture0 = Texture("../res/models/head/lambertian.jpg");

	/*
	Material:
		vec4 emission;    // Ecm
		vec4 ambient;     // Acm
		vec4 diffuse;     // Dcm
		vec4 specular;    // Scm
		float shininess;  // Srm
	*/

	Transformation trans = Transformation();

	// Model (Mesh / Material)
	// Entity (Model / Trans)

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
				trans.ChangeRotation(glm::vec3(0, glm::radians(100.0f), 0));
			}
			if (e.key.keysym.sym == SDLK_t) {
				trans.ChangeRotation(glm::vec3(0, glm::radians(-100.0f), 0));
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
		float time = sinf(SDL_GetTicks() / 500.0f) * 10;

		// Clear
		window.clear();

		// 3D Render
		shader.Bind();

		// Bind Textures using texture units
		texture0.Bind(0);
		glUniform1i(glGetUniformLocation(shader.GetId(), "texture0"), 0);

		// Model
		glm::mat4 view = camera.GetViewMatrix();

		glm::mat4 projection = glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f);

		shader.SetUniform4fv("model", trans.GetTransformationMatrix());
		shader.SetUniform4fv("view", view);
		shader.SetUniform4fv("projection", projection);

		vec3 viewPos = camera.Position;
		shader.SetUniform3fv("viewPos", viewPos);

		shader.SetUniform3fv("lightPosition", vec3(time, 0, 10));
		shader.SetUniform3fv("lightColor", vec3(1, 1, 1));

		mesh.render();

		shader.Unbind();

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

	mesh.~Mesh();
	debugUi.cleanUp();
	window.cleanUp();

	return EXIT_SUCCESS;
}