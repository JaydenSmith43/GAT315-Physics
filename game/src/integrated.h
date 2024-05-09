#pragma once
#include "body.h"
#include "raylib.h"

inline void ExplicitEuler(opBody* body, float timestep) //dt
{
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
}	

inline void SemiImplicitEuler(opBody* body, float timestep)
{
	body->velocity = Vector2Add(body->velocity, Vector2Scale(body->acceleration, timestep));
	body->position = Vector2Add(body->position, Vector2Scale(body->velocity, timestep));
}