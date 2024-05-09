#pragma once
#include "raylib.h"
#include "raymath.h"

typedef enum //unscoped
{
	BT_STATIC,
	BT_KINEMATIC,
	BT_DYNAMIC
} opBodyType;

typedef enum
{
	FM_FORCE,
	FM_IMPULSE,
	FM_VELOCITY
} opForceMode;

typedef struct opBody //define it is struct
{
	opBodyType type;

	// acceleration -> velocity -> position
	Vector2 position;
	Vector2 velocity;
	Vector2 acceleration;
	Vector2 force;

	float mass;
	float inverseMass; // 1/mass (static = 0)
	float gravityScale;
	float damping;
	Color color;

	struct opBody* next;
	struct opBody* prev;

} opBody; //define it is of type body

inline void ApplyForce(opBody* body, Vector2 force, opForceMode forceMode)
{
	if (body->type != BT_DYNAMIC) return;

	switch (forceMode)
	{
	case FM_FORCE:
		body->force = Vector2Add(body->force, force);
		break;
	case FM_IMPULSE:
		// applies a sudden change in momentum
		body->velocity = Vector2Scale(force, body->inverseMass);
		break;
	case FM_VELOCITY:
		body->velocity = force;
		break;
	}
}

inline void ClearForce(opBody* body)
{
	body->force = Vector2Zero();
}

void Step(opBody* body, float timestep);