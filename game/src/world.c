#include "world.h"
#include "body.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

opBody* opBodies = NULL;
int opBodyCount = 0;
Vector2 opGravity;

opBody* CreateBody()
{
	opBody* newBody = (opBody*)malloc(sizeof(opBody)); //*opBodyCount + 1
	assert(newBody);

	memset(newBody, 0, sizeof(opBody));

	newBody->prev = NULL;
	newBody->next = opBodies; //set to current head

	if (opBodies != NULL)
	{
		opBodies->prev = opBodies; //set to current head
	}

	opBodies = newBody; //head is set to new body
	opBodyCount++;
	
	return newBody;
}
void DestroyBody(opBody* body)
{
	//Assert if provided opBody is not NULL
	assert(body != NULL);

	//If 'prev' is not NULL, set 'prev->next' to 'body->next'
	if (body->prev != NULL)
	{
		body->prev->next = body->next;
	}
	
	//If 'next' is not NULL, set 'next->prev' to 'body->prev'
	if (body->next != NULL)
	{
		body->next->prev = body->prev;
	}

	//If body is the head, update head to 'body->next'
	if (body->next == NULL)
	{
		body = body->next;
	}

	//Decrement body count
	opBodyCount--;

	//Free the body
	free(body);
}

void DestroyAllBodies()
{
	//free(opBodies);
}