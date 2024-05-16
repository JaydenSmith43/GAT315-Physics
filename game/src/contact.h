#pragma once
#include "raylib.h"

typedef struct opContact
{
	struct opBody* body1;
	struct opBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct opContact* next;
} opContact_t;

void AddContact(opContact_t* contact, opContact_t** contacts);
void DestroyAllContacts(opContact_t** contacts);
