#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "raymath.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 10

int main(void)
{
	InitWindow(800, 450, "Phsyics Engine");
	SetTargetFPS(60);

	//Body* bodies = new Body[20];
	Body* bodies = (Body*)malloc(sizeof(Body) * MAX_BODIES);
	assert(bodies != NULL);

	int bodyCount = 0; //default to 0

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		Vector2 position = GetMousePosition();
		if (IsMouseButtonPressed(0))
		{
			bodies[bodyCount].position = position;
			bodies[bodyCount].velocity = CreateVector2(GetRandomFloatValue(-5, 5), GetRandomFloatValue(-5, 5));
			bodyCount++;
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK); //RAYWHITE

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME); //print format
		DrawText(TextFormat("FRAME: %.4f ", dt), 10, 30, 20, LIME);
		
		//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);
		DrawCircle((int)position.x, (int)position.y, 10, YELLOW);
		for (int i = 0; i < bodyCount; i++)
		{
			bodies[i].position = Vector2Add(bodies[i].position, bodies[i].velocity);

			DrawCircle((int)bodies[i].position.x, (int)bodies[i].position.y, 10, RED);
		}
		
		EndDrawing();
	}

	CloseWindow();
	free(bodies);

	return 0;
}