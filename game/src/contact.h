#pragma once
#include "raylib.h"

typedef struct opContact
{
	struct ncBody* body1;
	struct ncBody* body2;

	float restitution;
	float depth;
	Vector2 normal;

	struct opContact* next;
} opContact_t;

void AddContact(opContact_t* contact, opContact_t** contacts);
void DestroyAllContacts(opContact_t** contacts);
