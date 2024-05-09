#include "body.h"
#include "integrated.h"
#include "world.h"

void Step(opBody* body, float timestep)
{
	body->force = Vector2Add(body->force, Vector2Scale(Vector2Scale(opGravity, body->gravityScale), body->mass));
	body->acceleration = Vector2Scale(body->force, body->inverseMass);

	SemiImplicitEuler(body, timestep);

	//apply damping
	float damping = 1/ (1 + body->damping * timestep);
	body->velocity = Vector2Scale(body->velocity, damping);

	ClearForce(body);
}