#pragma once
#include "body.h"

extern Body* bodies; //so that it is created one time when included in multiple places
extern int bodyCount;

Body* CreateBody();
void DestroyBody(Body* body);
//declare functions only once in world.c