#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"

auto window = Window("OpenGL 2D Skeleton", 1280, 720);

void step () {

	window.update();

	window.clear();

	window.swap();
}

#undef main
int main(int argc, char *argv[])
{
	printf("%s\n", "Entering main loop");

	while (!window.isCloseRequested()) {
		step();	
	}
	
	return 0;
}