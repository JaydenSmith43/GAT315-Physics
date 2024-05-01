#include "body.h"
#include "mathf.h"
#include "raylib.h"

#include "raymath.h"
#include "world.h"
#include "integrated.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 1000

int main(void)
{
	InitWindow(1280, 720, "Physics Engine");
	SetTargetFPS(60);

	//opBody* opBodies = new opBody[20];
	//opBody* opBodies = (opBody*)malloc(sizeof(opBody) * MAX_BODIES);
	//assert(opBodies != NULL);

	//int opBodyCount = 0; //default to 0

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonDown(0))
		{
			opBody* body = CreateBody();
			body->position = position;
			body->mass = GetRandomFloatValue(1,5);
		} //ApplyForce(body, CreateVector2(GetRandomFloatValue(-50, 50), GetRandomFloatValue(-50, 50)));

		// apply force opBodies
		opBody* body = opBodies;
		while (body)
		{
			ApplyForce(body, CreateVector2(0, -50));
			body = body->next;
		}

		// update opBodies
		body = opBodies;
		while (body)
		{
			//body->position = Vector2Add(body->position, body->velocity);
			ExplicitEuler(body, dt);
			ClearForce(body);
			body = body->next; // get next body
		}

		

		// Render
		BeginDrawing();
		ClearBackground(BLACK); //RAYWHITE

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME); //print format
		DrawText(TextFormat("FRAME: %.4f ", dt), 10, 30, 20, LIME);
		
		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		// draw opBodies
		body = opBodies;
		while (body) // do while we have a valid pointer, will be NULL at the end of the list
		{
			DrawCircle((int)body->position.x, (int)body->position.y, body->mass, RED);
			body = body->next; // get next body
		}
		
		EndDrawing();
	}

	CloseWindow();
	free(opBodies);

	return 0;
}