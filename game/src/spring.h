#pragma once

typedef struct opSpring
{
	struct opBody* body1;
	struct opBody* body2;
	float restLength;
	float k; // stiffness

	struct opSpring* next;
	struct opSpring* prev;
} opSpring_t;

extern opSpring_t* opSprings;

opSpring_t* CreateSpring(struct opBody* body1, struct opBody* body2, float restLength, float k);
void AddSpring(opSpring_t* spring);
void DestroySpring(opSpring_t* spring);
void DestroyAllSprings();

void ApplySpringForce(opSpring_t* spring);