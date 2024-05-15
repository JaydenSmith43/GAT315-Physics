#include "collision.h"
#include "contact.h"
#include "body.h"
#include "mathf.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>


bool Intersects(opBody* body1, opBody* body2) //for circles
{
	// if distance <= radius
	float distance = Vector2Distance(body1->position, body2->position);
	float radius = body1->mass + body2->mass;

	return (distance <= radius); //if true, return true
}

void CreateContacts(opBody* bodies, opContact_t** contacts)
{
	for (opBody* body1 = bodies; body1; body1 = body1->next)
	{
		for (opBody* body2 = body1->next; body2; body2 = body2->next)
		{
			if (body1 == body2) continue;
			if (body1->type != BT_DYNAMIC && body2->type != BT_DYNAMIC) continue;

			if (Intersects(body1, body2))
			{
				opContact_t* contact = GenerateContact(body1, body2);
				AddContact(contact, contacts);
			}
		}
	}
}

opContact_t* GenerateContact(opBody* body1, opBody* body2)
{
	opContact_t* contact = (opContact_t*)malloc(sizeof(opContact_t));
	assert(contact);

	memset(contact, 0, sizeof(opContact_t));

	contact->body1 = body1;
	contact->body2 = body2;

	Vector2 direction = Vector2Subtract(body1->position, body2->position);
	float distance = Vector2Length(direction);
	if (distance == 0)
	{
		direction = (Vector2){ GetRandomFloatValue(-0.05f, 0.05f), GetRandomFloatValue(-0.05f, 0.05f) };
	}

	float radius = (body1->mass + body2->mass);

	contact->depth = radius - distance;
	contact->normal = Vector2Normalize(direction);
	contact->restitution = (body1->restitution + body2->restitution) * 0.5f;

	return contact;
}

void SeparateContacts(opContact_t* contacts)
{

}

void ResolveContacts(opContact_t* contacts)
{

}
