#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <vector>

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

	srand(time(0));
	//std::vector<Entity> entities;

	//Loader loader = Loader();
	//RawModel mBox = OBJLoader::LoadObjModel("model", loader);
	//ModelTexture mtBox(loader.LoadTexture("model"));
	//TexturedModel tmBox(mBox, mtBox);
	//Entity entity = Entity(tmBox, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), glm::vec3(1, 1, 1));
	//entities.push_back();

	// Main loop
	bool running = true;
	SDL_Event e;
	while (!window.isCloseRequested()) {

		// Poll inputs
		while (SDL_PollEvent(&e)) {
			debugUi.processEvents(e);
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				window.requestClose();
			}
		}

		// Update
		//camera.Update();

		// Render 
		debugUi.prepare();
		window.clear();

		//for (Entity& e : entities)
		//	renderer.ProcessEntity(e);

		//renderer.Render(light, camera);

		debugUi.render();

		window.swap();
	}
	window.cleanUp();

	return 0;
}