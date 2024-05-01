#pragma once
#include "body.h"
#include "raylib.h"

void ExplicitEuler(opBody* body, float timestep) //dt
{
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(Vector2Scale(body->force, 1 / body->mass), timestep));
}	