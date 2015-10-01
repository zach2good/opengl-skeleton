#pragma once

#include <SDL.h>

#include <GL\glew.h>
#include <GL\GL.h>
#include <GL\GLU.h>

#include <stdio.h>

#include <entities\Entity.h>

class BasicRenderer
{
public:
	BasicRenderer();
	~BasicRenderer();

	void Prepare();
	void Submit(Entity e);
	void Render();

private:

};
