#include "common.h"
#include <string.h>


class Material
{
public:
	Texture diffuse;
	Texture specular;
	float shininess;

	Material(Texture tex)
		: diffuse(tex), specular(tex)
	{
		shininess = 32.0f;
	}

	Material(Texture d, Texture s)
		: diffuse(d), specular(s)
	{
		shininess = 32.0f;
	}
};


int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);
	DebugUi debugUi = DebugUi(window.getWindow());

	Camera camera = Camera();
	camera.Position = vec3(0, 0, 5);

	ShaderProgram basicShader = ShaderProgram("../res/shaders/basicShader");
	ShaderProgram lampShader = ShaderProgram("../res/shaders/lampShader");

	Mesh objectMesh = Mesh("../res/models/head/head.obj");	
	Texture texture = Texture("../res/models/head/lambertian.jpg");

	Mesh lightMesh = Mesh("../res/models/cube.obj");

	Transformation objectTrans = Transformation();
	objectTrans.SetScale(vec3(5.8f));

	Transformation lightTrans = Transformation();
	lightTrans.SetPosition(vec3(1, 1, 1));
	lightTrans.SetScale(vec3(0.2f));

	texture.Bind(0);
	texture.Bind(1);

	Material material = Material(texture);

	DirLight dirLight = DirLight(vec3(-0.2f, -1.0f, -0.3f));
	PointLight pointLight = PointLight(vec3());
	SpotLight spotLight = SpotLight(camera.Position, camera.Front);

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
		float time = SDL_GetTicks() / 500.0f;
		float time_sin = sinf(SDL_GetTicks() / 500.0f);
		float time_cos = cosf(SDL_GetTicks() / 500.0f);
		objectTrans.SetRotation(vec3(0, time, 0));
		lightTrans.SetPosition(vec3(time_sin * 2, 0, time_cos * 2));
		pointLight.position = lightTrans.GetPosition();

		// Clear
		window.clear();

		// 3D Render
		basicShader.Bind();

		// Model, View and World Matrices
		basicShader.SetUniform4fv("model", objectTrans.GetTransformationMatrix());
		basicShader.SetUniform4fv("view", camera.GetViewMatrix());
		basicShader.SetUniform4fv("projection", glm::perspective(camera.Zoom, (float)window.getWidth() / (float)window.getHeight(), 0.1f, 1000.0f));

		// Camera Position
		basicShader.SetUniform3fv("viewPos", camera.Position);

		// Material
		basicShader.SetUniform1i("material.diffuse", material.diffuse.GetTextureID()); //0
		basicShader.SetUniform1i("material.specular", material.specular.GetTextureID()); //1
		basicShader.SetUniform1f("material.shininess", material.shininess);

		// Directional light
		basicShader.SetUniform3fv("dirLight.direction", dirLight.direction);
		basicShader.SetUniform3fv("dirLight.ambient", dirLight.ambient);
		basicShader.SetUniform3fv("dirLight.diffuse", dirLight.diffuse);
		basicShader.SetUniform3fv("dirLight.specular", dirLight.specular);

		// Point Light
		basicShader.SetUniform3fv("pointLight.position", pointLight.position);
		basicShader.SetUniform3fv("pointLight.ambient", pointLight.ambient);
		basicShader.SetUniform3fv("pointLight.diffuse", pointLight.diffuse);
		basicShader.SetUniform3fv("pointLight.specular", pointLight.specular);
		basicShader.SetUniform1f("pointLight.constant", pointLight.constant);
		basicShader.SetUniform1f("pointLight.linear", pointLight.linear);
		basicShader.SetUniform1f("pointLight.quadratic", pointLight.quadratic);

		// Spot Light
		basicShader.SetUniform3fv("spotLight.position", spotLight.position);
		basicShader.SetUniform3fv("spotLight.direction", spotLight.direction);
		basicShader.SetUniform3fv("spotLight.ambient", spotLight.ambient);
		basicShader.SetUniform3fv("spotLight.diffuse", spotLight.diffuse);
		basicShader.SetUniform3fv("spotLight.specular", spotLight.specular);
		basicShader.SetUniform1f("spotLight.constant", spotLight.constant);
		basicShader.SetUniform1f("spotLight.linear", spotLight.linear);
		basicShader.SetUniform1f("spotLight.quadratic", spotLight.quadratic);
		basicShader.SetUniform1f("spotLight.cutOff", spotLight.cutOff);
		basicShader.SetUniform1f("spotLight.outerCutOff", spotLight.outerCutOff);

		objectMesh.render();

		basicShader.Unbind();

		// Draw White Lights
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