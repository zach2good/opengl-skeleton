#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/DebugUi.h"

#include "scenes/Scene1.h"

auto window = new Window("OpenGL Skeleton", 1280, 720);
auto scene = new Scene1(window);

void step () {

	window->update();
	scene->update();

	window->clear();

	scene->render();

	window->swap();
}

#undef main
int main(int argc, char *argv[])
{
	printf("%s\n", "Starting...");

	scene->init();

	while (!window->isCloseRequested()) {
		step();	
	}

	scene->destroy();

	delete scene;
	delete window;
	
	return 0;
}