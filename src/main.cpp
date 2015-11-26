#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/DebugUi.h"

#include "scenes/Scene1.h" // Quad
#include "scenes/Scene2.h" // Texture Map
#include "scenes/Scene3.h" // 3D Textured Box
#include "scenes/Scene4.h" // Basic Lighting
#include "scenes/Scene5.h" // Framebuffer
#include "scenes/Scene6.h" // Blinn-Phong Shading

// Depth
// Stencil
// Blending

// Cubemaps
// Instanced Rendering
// Advanced Lighting

// Gamma
// Shadows
// Normal Mapping
// Parallax Mapping

// HDR
// Bloom

// Deferred
// SSAO

Window* window = new Window("OpenGL Skeleton", 800, 600);
auto scene = new Scene6(window);

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

	//delete scene;
	//delete window;

	return 0;
}