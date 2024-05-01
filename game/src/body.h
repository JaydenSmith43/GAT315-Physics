#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum
{
	STATIC,
	KINEMATIC,
	DYNAMIC
} opBodyType;

typedef struct opBody //define it is struct
{
	opBodyType type;

	// force -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 force;

	float mass;
	float inverseMass; // 1/mass (static = 0)

	struct opBody* next;
	struct opBody* prev;

} opBody; //define it is of type body

inline void ApplyForce(opBody* body, Vector2 force)
{
	body->force = Vector2Add(body->force, force);
}

inline void ClearForce(opBody* body)
{
	body->force = Vector2Zero();
}