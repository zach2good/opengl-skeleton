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
		boids.push_back(Boid(input.getPos().x, input.getPos().y));
	}

	if (input.isMouseDown(SDL_BUTTON_RIGHT))
	{
	}

	for (int i = 0; i < boids.size(); i++)
	{
		Boid& b = boids.at(i);
		b.run(&boids);
	}
}
void BoidsScene2D::render()
{
	for (int i = 0; i < boids.size(); i++)
	{
		vec2 p = boids.at(i).pos;
		m_Window->drawRect(p.x - 10, p.y - 10, p.x + 10, p.y + 10, 100, 100, 100);
	}

}
