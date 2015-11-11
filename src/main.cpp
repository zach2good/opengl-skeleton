#include <stdio.h>
#include <SDL.h>

#include "core/assimp.h"

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/ShaderProgram.h"
#include "graphics/Camera.h"

auto window = Window("OpenGL Skeleton", 1280, 720);
auto shader = ShaderProgram("res/shaders/basicShader");

void step () {
	window.update();
	window.clear();

	shader.Bind();

	shader.Unbind();
	
	window.swap();
}

#undef main
int main(int argc, char *argv[])
{
	printf("%s\n", "Entering main loop");

	auto camera = Camera();
	camera.Position = vec3(0, 0, 5);

	#ifdef EMSCRIPTEN
	emscripten_set_main_loop(step, 0, true);
	#else
	while (!window.isCloseRequested()) {
		step();	
	}
	#endif


	
	return 0;
}