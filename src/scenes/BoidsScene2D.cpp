#include "BoidsScene2D.h"

void BoidsScene2D::init()
{
	srand(time(NULL));

	boids = std::vector<Boid>();

	for (int i = 0; i < numBoids; i++)
	{
		int x = rand() % 800 + 1;
		int y = rand() % 600 + 1;
		boids.push_back(Boid(x, y));
	}	
}

void BoidsScene2D::destroy()
{

}

void BoidsScene2D::update()
{
	Input& input = Input::instance();

	if (input.isKeyDown(SDL_SCANCODE_A)) 
	{
	}

	if (input.isKeyDown(SDL_SCANCODE_D)) 
	{
	}

	if (input.isKeyDown(SDL_SCANCODE_W)) 
	{
	}

	if (input.isKeyDown(SDL_SCANCODE_S)) 
	{
	}

	if (input.isMouseDown(SDL_BUTTON_LEFT))
	{
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
	}

	// 1 : separation: steer to avoid crowding local flockmates
	// 2 : alignment : steer towards the average heading of local flockmates
	// 3 : cohesion : steer to move toward the average position(center of mass) of local flockmates
	vec2 sep = separate(boids);
	vec2 ali = align(boids);
	vec2 coh = cohesion(boids);

	sep *= 1.5f;
	ali *= 1.0f;
	coh *= 1.0f;

	for (int i = 0; i < numBoids; i++)
	{
		Boid& b = boids.at(i);

		b.applyForce(sep.x, sep.y);
		b.applyForce(ali.x, ali.y);
		b.applyForce(coh.x, coh.y);
		
		b.vel += b.acc;

		if (b.vel.x > b.maxspeed) { b.vel.x = b.maxspeed; }
		else if (b.vel.x < -b.maxspeed) { b.vel.x = -b.maxspeed; }

		else if (b.vel.y > b.maxspeed) { b.vel.y = b.maxspeed; }
		else if (b.vel.y < -b.maxspeed) { b.vel.y = -b.maxspeed; }

		b.pos += b.vel;
		b.acc *= 0.0f;
	}
}

vec2 BoidsScene2D::separate(std::vector<Boid> boids)
{

	return vec2(0);
}

vec2 BoidsScene2D::align(std::vector<Boid> boids)
{

	return vec2(0);
}

vec2 BoidsScene2D::cohesion(std::vector<Boid> boids)
{
	return vec2(0);
}

void BoidsScene2D::render()
{
	for (int i = 0; i < numBoids; i++)
	{
		vec2 p = boids.at(i).pos;
		m_Window->drawRect(p.x - 10, p.y - 10, p.x + 10, p.y + 10, 100, 100, 100);
	}
	
}
