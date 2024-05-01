#include "world.h"
#include <stdlib.h>
#include <assert.h>

Body* bodies = NULL;
int bodyCount = 0;

Body* CreateBody()
{
	//Allocate memory for a new Body using malloc.
	Body* newBody = (Body*)malloc(sizeof(Body)); //*bodyCount + 1
	
	//Assert that the allocation was successful.
	assert(newBody != NULL);

	//Set the new body’s prev pointer to NULL and its next pointer to the current head of the list(bodies).
	newBody->prev = NULL;
	newBody->next = bodies;

	//If the list is not empty, update the prev pointer of the current head.
	if (bodies != NULL)
	{
		bodies->prev = bodies;
	}
	
	//Set the bodies to the new Body
	bodies = newBody;

	//Increment body count
	bodyCount++;
	
	
	//Return the new Body.
	return newBody;
}
void DestroyBody(Body* body)
{
	//Assert if provided Body is not NULL
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
	bodyCount--;

	//Free the body
	free(body);
}