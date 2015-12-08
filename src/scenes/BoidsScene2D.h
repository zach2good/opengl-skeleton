#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window2D.h"
#include "../core/Input.h"

// http://natureofcode.com/book/chapter-6-autonomous-agents/

struct Boid
{
public:
	vec2 pos;
	vec2 vel;
	vec2 acc;

	float maxforce = 15.0f;
	float maxspeed = 4.0f;

	Boid() : pos(0), vel(0), acc(0) {}
	Boid(int x, int y) : pos(vec2(x,y)), vel(0), acc(0) {}
	Boid(int x, int y, int dx, int dy, int ax, int ay) : pos(vec2(x, y)), vel(vec2(dx, dy)), acc(vec2(ax, ay)) {}

	void applyForce(int x, int y) { acc += vec2(x, y); }
	float magSq() {	return vel.x*vel.x + vel.y*vel.y; }
};

class BoidsScene2D
{
public:
	BoidsScene2D(Window2D* window) : m_Window(window) {};

	void init();
	void destroy();

	void update();
	void render();

private:

	Window2D* m_Window;

	int numBoids = 20;
	std::vector<Boid> boids;
	vec2 separate(std::vector<Boid> boids);
	vec2 align(std::vector<Boid> boids);
	vec2 cohesion(std::vector<Boid> boids);

};
