#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/Window.h"

#include "graphics/ShaderProgram.h"

#include "graphics/Camera.h"

auto window = Window("OpenGL Skeleton", 1280, 720);

void step () {
	window.update();
	window.clear();
	window.swap();
}

int main(int argc, char *argv[])
{
	printf("%s\n", "Entering main loop");

	auto camera = Camera();
	camera.Position = vec3(0, 0, 5);

	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(step, 0, true);
	#else
	while (true) {
		// Desktop Specific
		if (window.isCloseRequested())
		{
			break;
		}
		step();	
	}
	#endif


	
	return 0;
}