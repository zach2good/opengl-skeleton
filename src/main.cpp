#include <stdio.h>
#include <SDL.h>

#include "graphics/GL.h"
#include "graphics/glm.h"

#include "graphics/Window.h"
#include "graphics/Window2D.h"
#include "graphics/DebugUi.h"

#include "scenes/BoidsScene2D.h"

#include "scenes/Scene1.h" // Quad
#include "scenes/Scene2.h" // Texture Map
#include "scenes/Scene3.h" // 3D Textured Box
#include "scenes/Scene4.h" // Basic Lighting
#include "scenes/Scene5.h" // Framebuffer Testing
#include "scenes/Scene6.h" // Blinn-Phong Shading

// Depth
// Stencil
// Blending

// Particles 

// Input, Picking, Dragging

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

auto window = new Window2D("OpenGL Skeleton", 800, 600);
//auto scene = new Scene5(window);
auto scene = new BoidsScene2D(window);

void step() {

	window->update();
	window->clear();

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

	delete scene;
	delete window;

	return 0;
}