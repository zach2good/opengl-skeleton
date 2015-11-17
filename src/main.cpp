#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window2D.h"

auto window = Window2D("OpenGL 2D Skeleton", 1280, 720);

void step () {

	window.update();

	window.clear();

	for (int i = 0; i < 200; ++i)
	{
		window.drawPixel(10 + i, 10 + i, 255, 255, 255);
	}	

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