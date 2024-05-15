#pragma once
#include "raylib.h"

typedef struct opContact opContact_t;
typedef struct opBody opBody;

void CreateContacts(opBody* bodies, opContact_t** contacts);
opContact_t* GenerateContact(opBody* body1, opBody* body2);

void SeparateContacts(opContact_t* contacts);
void ResolveContacts(opContact_t* contacts);