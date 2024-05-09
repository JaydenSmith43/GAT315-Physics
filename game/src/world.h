#pragma once
//#include "body.h"
#include "raylib.h"

typedef struct opBody opBody;

extern opBody* opBodies; //so that it is created one time when included in multiple places
extern int opBodyCount;
extern Vector2 opGravity;

opBody* CreateBody();
void DestroyBody(opBody* body);
void DestroyAllBodies();
//declare functions only once in world.c