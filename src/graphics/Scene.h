#pragma once

#include "../common.h"

class Scene
{
public:
	virtual void init();
	virtual void destroy();

	virtual void update();
	virtual void render();	
};