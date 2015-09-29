#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <glm\glm.hpp>

#include <graphics\Window.h>
#include <utils\DebugUi.h>

int main(int argc, char *argv[])
{
	Window window = Window("OpenGL Skeleton", 1280, 720);

	DebugUi debugUi = DebugUi(window.getWindow());

	// Main loop
	bool running = true;
	SDL_Event e;
	while (!window.isCloseRequested()) {

		// Poll inputs
		// TODO: Move to input manager
		while (SDL_PollEvent(&e)) {
			debugUi.processEvents(e);
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				window.requestClose();
			}
		}

		debugUi.prepare();
		window.clear();

		// Render
		// TODO: Split out into Renderer: renderer.render();
		//glBindVertexArray(vaoHandle);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		debugUi.render();

		window.swap();
	}
	window.cleanUp();

	return 0;
}