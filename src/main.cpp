#include <stdio.h>
#include <memory>

#include "graphics/Window.h"
#include "graphics/DebugUi.h"
#include "scenes/GScene1.h"

std::unique_ptr<Window> window(new Window("OpenGL Skeleton", 1280, 720));
std::unique_ptr<GScene1> scene(new GScene1(window.get()));

void step() {

	window->update();

	scene->update();

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

	return 0;
}