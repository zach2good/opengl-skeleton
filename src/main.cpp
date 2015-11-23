#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/DebugUi.h"
#include "graphics/ForwardScene.h"

auto window = new Window("OpenGL Skeleton", 1280, 720);
//auto debug = new DebugUi(window->getWindow());
auto scene = new ForwardScene(window);

void step () {

	window->update();
	scene->update();

	window->clear();

	scene->render();

	//debug->prepare();
	//debug->render();

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
	//delete debug;
	delete window;
	
	return 0;
}