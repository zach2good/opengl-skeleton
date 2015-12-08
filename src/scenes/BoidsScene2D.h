#pragma once

#include "Scene.h"

#include "../common.h"

#include "../core/Timer.h"
#include "../core/Util.h"

#include "../graphics/Window2D.h"
#include "../core/Input.h"

// http://natureofcode.com/book/chapter-6-autonomous-agents/
// http://www.behaviorworks.com/people/ckline/cornellwww/boid/boids.html

class Boid
{
public:
	std::vector<Boid>* boids;

	vec2 pos;
	vec2 vel;
	vec2 acc;

	float maxforce = 0.1f;
	float maxspeed = 4.0f;

	vec2 maxForceV = vec2(maxforce);
	vec2 maxSpeedV = vec2(maxforce);

	Boid() : pos(0), vel(0), acc(0) {}
	Boid(int x, int y) : pos(vec2(x, y)), vel(0), acc(0) {}
	Boid(int x, int y, int dx, int dy, int ax, int ay) : pos(vec2(x, y)), vel(vec2(dx, dy)), acc(vec2(ax, ay)) {}

	void applyForce(int x, int y) 
	{ 
		acc += vec2(x, y); 
	}

	void applyForce(vec2 v)
	{
		acc += v;
	}

	float magSq() 
	{ 
		return vel.x*vel.x + vel.y*vel.y; 
	}

	void run(std::vector<Boid>* boids)
	{
		flock(boids);
		update();
		borders();
		
	}

	void flock(std::vector<Boid>* boids)
	{
		vec2 sep = separate(boids);   // Separation
		vec2 ali = align(boids);      // Alignment
		vec2 coh = cohesion(boids);   // Cohesion

		// Arbitrarily weight these forces
		sep *= 1.5f;
		ali *= 1.0f;
		coh *= 1.0f;

		// Add the force vectors to acceleration
		applyForce(sep);
		applyForce(ali);
		applyForce(coh);
	}

	void update()
	{
		vel += acc;

		if (vel.x > maxspeed) { vel.x = maxspeed; }
		else if (vel.x < -maxspeed) { vel.x = -maxspeed; }

		else if (vel.y > maxspeed) { vel.y = maxspeed; }
		else if (vel.y < -maxspeed) { vel.y = -maxspeed; }

		pos += vel;
		acc *= 0.0f;
	}

	void borders()
	{
		if (pos.x < 0) { pos.x = 800; }
		if (pos.x > 800) { pos.x = 0; }

		if (pos.y < 0) { pos.y = 600; }
		if (pos.y > 600) { pos.y = 0; }
	}

	vec2 seek(vec2 target) 
	{
		vec2 desired = target - pos;

		glm::normalize(desired);
		desired *= maxspeed;

		// Steering = Desired minus Velocity
		vec2 steer = desired - vel;

		//glm::clamp(steer, -maxForceV, maxForceV);
		steer *= maxforce;

		return steer;
	}

	vec2 separate(std::vector<Boid>* boids)
	{
		float desiredseparation = 25.0f;
		vec2 steer = vec2(0);
		int count = 0;

		// For every boid in the system, check if it's too close
		for (int i = 0; i < boids->size(); i++)
		{
			Boid other = boids->at(i);

			float d = glm::distance(pos, other.pos);

			// If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
			if ((d > 0) && (d < desiredseparation)) {
				// Calculate vector pointing away from neighbor
				vec2 diff = pos - other.pos;

				//diff.normalize();
				diff /= d;        // Weight by distance
				steer += diff;
				count++;            // Keep track of how many
			}
		}

		// Average -- divide by how many
		if (count > 0) {
			steer /= (float)count;
		}

		// As long as the vector is greater than 0
		if (glm::length(steer) > 0) {
			// First two lines of code below could be condensed with new PVector setMag() method
			// Not using this method until Processing.js catches up
			// steer.setMag(maxspeed);

			// Implement Reynolds: Steering = Desired - Velocity
			glm::normalize(steer);
			steer *= maxspeed;
			steer -= vel;

			//glm::clamp(steer, -maxForceV, maxForceV);
			steer *= maxforce;
		}
		return steer;
	}

	vec2 align(std::vector<Boid>* boids)
	{
		float neighbordist = 50.0f;
		vec2 sum = vec2(0);
		int count = 0;

		for (int i = 0; i < boids->size(); i++)
		{
			Boid other = boids->at(i);
			float d = glm::distance(pos, other.pos);
			if ((d > 0) && (d < neighbordist)) {
				sum += other.vel;
				count++;
			}
		}

		if (count > 0) {
			sum /= (float)count;
			// First two lines of code below could be condensed with new PVector setMag() method
			// Not using this method until Processing.js catches up
			// sum.setMag(maxspeed);

			// Implement Reynolds: Steering = Desired - Velocity
			glm::normalize(sum);
			sum *= maxspeed;
			vec2 steer = sum - vel;
			
			//glm::clamp(steer, -maxForceV, maxForceV);
			steer *= maxforce;

			return steer;
		}
		else 
		{
			return vec2(0);
		}
	}

	vec2 cohesion(std::vector<Boid>* boids)
	{
		float neighbordist = 50;
		vec2 sum = vec2(0);   // Start with empty vector to accumulate all locations
		int count = 0;

		for (int i = 0; i < boids->size(); i++)
		{
			Boid other = boids->at(i);
			float d = glm::distance(pos, other.pos);
			if ((d > 0) && (d < neighbordist)) {
				sum += other.pos; // Add location
				count++;
			}
		}
		if (count > 0) {
			sum /= count;
			return seek(sum);  // Steer towards the location
		}
		else {
			return vec2(0);
		}
	}
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
