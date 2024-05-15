#include "spring.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

opSpring_t* opSprings = NULL;

opSpring_t* CreateSpring(struct opBody* body1, struct opBody* body2, float restLength, float k)
{
	opSpring_t* spring = (opSpring_t*)malloc(sizeof(opSpring_t));
	assert(spring);

	memset(spring, 0, sizeof(opSpring_t));
	spring->body1 = body1;
	spring->body2 = body2;
	spring->restLength = restLength;
	spring->k = k;

	return spring;
}

void AddSpring(opSpring_t* spring)
{
	assert(spring);

	spring->prev = NULL;
	spring->next = opSprings; //set to current head

	if (opSprings != NULL) opSprings->prev = opSprings; //set to current head


	opSprings = spring; //head is set to new body
}

void DestroySpring(opSpring_t* spring)
{
	//Assert if provided opBody is not NULL
	assert(spring);

	//If 'prev' is not NULL, set 'prev->next' to 'body->next'
	if (spring->prev != NULL)
	{
		spring->prev->next = spring->next;
	}

	//If 'next' is not NULL, set 'next->prev' to 'body->prev'
	if (spring->next != NULL)
	{
		spring->next->prev = spring->prev;
	}

	//If body is the head, update head to 'body->next'
	if (spring->next == NULL)
	{
		spring = spring->next;
	}

	//Free the body
	free(spring);
}

void DestroyAllSprings()
{
	//free(opSprings);
}

void ApplySpringForce(opSpring_t* spring)
{
	for (opSpring_t* spring = opSprings; spring; spring = spring->next)
	{
		Vector2 direction = Vector2Subtract(spring->body1->position, spring->body2->position);

		if (direction.x == 0 && direction.y == 0) continue;

		float length = Vector2Length(direction);
		float x = length - spring->restLength; //product of displacement
		float force = x * -spring->k;

		Vector2 ndirection = Vector2Normalize(direction);

		ApplyForce(spring->body1, Vector2Scale(ndirection, force), FM_FORCE);
		ApplyForce(spring->body2, Vector2Scale(Vector2Negate(ndirection), force), FM_FORCE);
	}
}
