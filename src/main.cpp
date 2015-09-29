#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <glm\glm.hpp>

#include <utils\DebugUi.h>

#define PROGRAM_NAME "OpenGL Skeleton"
#define WIDTH 1280
#define HEIGHT 720

int main(int argc, char *argv[])
{
	SDL_Window *m_Window;
	SDL_GLContext m_Context;

	//Start SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL Error");
	}

	// Set OpenGL Version Here
	// WARNING: Setting the version above 3 will disable Imgui as it is immediate mode
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	//SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);

	// Double Buffering and Z Depth
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	SDL_DisplayMode current;
	SDL_GetCurrentDisplayMode(0, &current);

	// Start a Window
	m_Window = SDL_CreateWindow(PROGRAM_NAME,
		SDL_WINDOWPOS_UNDEFINED,
		SDL_WINDOWPOS_UNDEFINED,
		WIDTH, HEIGHT,
		SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);

	if (!m_Window) {
		printf("Window Error");
	}

	// Start OpenGL Context
	m_Context = SDL_GL_CreateContext(m_Window);
	if (!m_Context) {
		printf("Context Error");
	}

	SDL_GL_SetSwapInterval(1);

	// Start GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() < 0) {
		printf("GLEW Error");
	}

	// Print Info
	printf("GL_VERSION: %s \n", glGetString(GL_VERSION));
	printf("GL_VENDOR: %s \n", glGetString(GL_VENDOR));
	printf("GL_SHADING_LANGUAGE_VERSION: %s \n", glGetString(GL_SHADING_LANGUAGE_VERSION));
	printf("GLEW_VERSION: %s \n", glewGetString(GLEW_VERSION));

	// Test GLM
	printf("GLM: %f \n", glm::vec4(glm::vec3(0.0), 1.0).a);

	// Debug UI
	DebugUi debugUi = DebugUi(m_Window);

	// Main loop
	bool running = true;
	SDL_Event e;
	while (running) {

		// Poll inputs
		while (SDL_PollEvent(&e)) {
			debugUi.processEvents(e);
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE) {
				running = false;
			}
		}

		debugUi.prepare();

		// Clear
		glViewport(0, 0, WIDTH, HEIGHT);
		glClearColor(0.2, 0.2, 0.2, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render
		//glBindVertexArray(vaoHandle);
		//glDrawArrays(GL_TRIANGLES, 0, 3);

		// Render Debug UI
		debugUi.render();

		// Swap
		SDL_GL_SwapWindow(m_Window);
	}

	// Cleanup
	SDL_GL_DeleteContext(m_Context);
	SDL_DestroyWindow(m_Window);
	SDL_Quit();

	return 0;
}