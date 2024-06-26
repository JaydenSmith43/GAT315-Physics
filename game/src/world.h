#pragma once
#include "raylib.h"

typedef struct opBody opBody;
typedef struct opContact opContact_t;
typedef enum opBodyType opBodyType;

extern opBody* opBodies; //so that it is created one time when included in multiple places
extern opContact_t* contacts;
extern int opBodyCount;
extern Vector2 opGravity;

opBody* CreateBody(Vector2 position, float mass, opBodyType bodyType);
void AddBody(opBody* body);
void DestroyBody(opBody* body);
void DestroyAllBodies();
//declare functions only once in world.c