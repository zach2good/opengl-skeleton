#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <graphics\Window.h>
#include <utils\DebugUi.h>
#include <utils\Maths.h>

#include <entities\Transformation.h>
#include <graphics\Loader.h>
#include <graphics\OBJLoader.h>
#include <graphics\shaders\ShaderProgram.h>
#include <graphics\models\Mesh.h>
#include <graphics\BasicRenderer.h>

#include <entities\Entity.h>
#include <entities\Camera.h>
#include <entities\Light.h>
#include <entities\Cube.h>

#include <graphics\textures\Texture.h>

#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", WIDTH, HEIGHT);
	DebugUi debugUi = DebugUi(window.getWindow());
	Camera camera = Camera().Position = glm::vec3(0.0, 4.0, 5.0);
	
	BasicRenderer renderer = BasicRenderer();


	Mesh m = OBJLoader::LoadFromFile("../res/models/dragon.obj", "../res/models/face.png");
	Transformation t = Transformation();
	t.SetPosition(glm::vec3(0.0f, 0.0f, -10.0f));

	Entity entity = Entity(m, t);	

	// Main loop
	bool running = true;
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

			if (e.type == SDL_MOUSEMOTION) {
				// TODO: Buggy, fix
				//int x, y;
				//SDL_GetRelativeMouseState(&x, &y);
				//camera.ProcessMouseMovement(x, -y);
			}
		}

		glPolygonMode(GL_FRONT_AND_BACK, (wireframe) ? GL_LINE : GL_FILL);

		// Update
		float timeVar = SDL_GetTicks() / 100.0f;

		// Clear / 3D Prepare
		renderer.Prepare();
		
		// Render 3D
		renderer.Submit(entity);	
		renderer.Render(camera);

		// Render 2D
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); }
		debugUi.prepare();
		debugUi.render();
		if (wireframe) { glPolygonMode(GL_FRONT_AND_BACK, GL_LINES); }


		window.swap();
	}

	window.cleanUp();

	return 0;
}