#include "contact.h"

#include <stdlib.h>
#include <assert.h>
#include <string.h>

//opContact_t* opContacts = NULL;

void AddContact(opContact_t* contact, opContact_t** contacts)
{
	assert(contact);

	// add element to linked list
	contact->next = *contacts;

	// set head of elements to new element
	*contacts = contact;
}

void DestroyAllContacts(opContact_t** contacts)
{
	if (!*contacts) return;

	opContact_t* contact = *contacts;
	while (contact)
	{
		opContact_t* next = contact->next;
		free(contact);
		contact = next;
	}

	*contacts = NULL;
}