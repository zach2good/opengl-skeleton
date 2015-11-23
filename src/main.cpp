#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/DebugUi.h"
#include "graphics/ForwardScene.h"

auto window = Window("OpenGL 2D Skeleton", 1280, 720);
auto debug = DebugUi(window.getWindow());
auto scene = ForwardScene();

void step () {

	window.update();
	scene.update();

	window.clear();
	scene.render();

	debug.prepare();
	debug.render();

	window.swap();
}

#undef main
int main(int argc, char *argv[])
{
	printf("%s\n", "Entering main loop");

	scene.init();

	while (!window.isCloseRequested()) {
		step();	
	}

	scene.destroy();
	
	return 0;
}