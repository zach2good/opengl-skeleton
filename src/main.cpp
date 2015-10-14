#include "common.h"

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);
	DebugUi debugUi = DebugUi(window.getWindow());
	ShaderProgram shader = ShaderProgram("../res/shaders/passThru");

	Camera camera = Camera();
	camera.Position = vec3(0.0, 0.0, 12.0);
	camera.LookAt(vec3()); // Look at 0,0,0

	while (!window.isCloseRequested()) {

		// Poll inputs
		SDL_Event e;
		while (SDL_PollEvent(&e)) {
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				window.requestClose();
			}
		}

		// Clear
		window.clear();

		// 3D Render
		shader.Bind();
		quad.Draw();
		shader.Unbind();

		// 2D Render
#ifdef _DEBUG 
		debugUi.prepare();
		debugUi.render();
#endif // _DEBUG 

		// Swap
		window.swap();
	}

	debugUi.cleanUp();
	window.cleanUp();

	return EXIT_SUCCESS;
}