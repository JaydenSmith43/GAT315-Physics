#pragma once
#include "body.h"

extern opBody* opBodies; //so that it is created one time when included in multiple places
extern int opBodyCount;

opBody* CreateBody();
void DestroyBody(opBody* body);
void DestroyAllBodies();
//declare functions only once in world.c