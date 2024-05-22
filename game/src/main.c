#include "body.h"
#include "mathf.h"
#include "raylib.h"
#include "force.h"
#include "spring.h"
#include "render.h"
#include "editor.h"
#include "collision.h"
#include "contact.h"

#include "raymath.h"
#include "world.h"
#include "integrated.h"

#include <stdlib.h>
#include <assert.h>

#define MAX_BODIES 1000

int main(void)
{
	opBody* selectedBody = NULL;
	opBody* connectBody = NULL;
		
	InitWindow(1280, 720, "Physics Engine");
	InitEditor();

	SetTargetFPS(60);

	// Initialize World
	opGravity = (Vector2){ 0, 30 }; //0,30

	float fixedTimeStep = 1.0f / 20;
	float timeAccumulator = 0.0f;

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		//float angle;
		Vector2 position = GetMousePosition();
		opScreenZoom += GetMouseWheelMove() * 0.2f;
		opScreenZoom = Clamp(opScreenZoom, 0.1f, 10);

		UpdateEditor(position);

		selectedBody = GetBodyIntersect(opBodies, position);
		if (selectedBody)
		{
			Vector2 screen = ConvertWorldToScreen(selectedBody->position);
			DrawCircleLines((int)screen.x, (int)screen.y, ConvertWorldToPixel(selectedBody->mass * 0.5f) + 5, YELLOW);
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsMouseButtonDown(MOUSE_BUTTON_LEFT) && IsKeyDown(KEY_LEFT_CONTROL)))
		{
			for (int i = 0; i < 1; i++)
			{
				opBody* body = CreateBody(ConvertScreenToWorld(position), opEditorData.Mass, opEditorData.BodyTypeActive);
				body->damping = opEditorData.BodyDamping; //opEditorData.BodyDamping //0,10
				body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
				body->gravityScale = -opEditorData.BodyGravityScale;// .GravityScaleValue 0,10
				body->restitution = 0.8f; //bounciness
				AddBody(body);
				//ApplyForce(body, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-500, -1000) }, FM_VELOCITY);//
			}
		}

		if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT) && selectedBody) connectBody = selectedBody;
		if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT) && connectBody) DrawLineBodyToPosition(connectBody, position);
		if (IsMouseButtonReleased(MOUSE_BUTTON_RIGHT) && connectBody)
		{
			if (selectedBody && selectedBody != connectBody)
			{
				opSpring_t* spring = CreateSpring(connectBody, selectedBody, Vector2Distance(connectBody->position, selectedBody->position), 20);
				AddSpring(spring);
			}
		}

		//opBody* body = opBodies;
		//while (body)
		//{
		//	ApplyForce(body, CreateVector2(0, 30), FM_FORCE);
		//	body = body->next;
		//}

		timeAccumulator += dt;
		while (timeAccumulator >= fixedTimeStep)
		{
			timeAccumulator -= fixedTimeStep;
			
			// apply force opBodies
			ApplyGravitation(opBodies, opEditorData.Gravitation);
			ApplySpringForce(opSprings);

			// update opBodies
			for (opBody* body = opBodies; body != NULL; body = body->next) //while not null
			{
				Step(body, fixedTimeStep);
			}

			// collision
			contacts = NULL;
			CreateContacts(opBodies, &contacts);
			SeparateContacts(contacts);
			ResolveContacts(contacts);
		}

		// Render
		BeginDrawing();
		ClearBackground(BLACK); //RAYWHITE

		DrawText(TextFormat("FPS: %.2f (%.2fms)", fps, 1000/fps), 10, 10, 20, LIME); //print format
		DrawText(TextFormat("FRAME: %.4f ", dt), 10, 30, 20, LIME);
		DrawText(TextFormat("BODIES: %i ", opBodyCount), 10, 50, 20, LIME);
		
		//DrawCircle((int)position.x, (int)position.y, 10, YELLOW);//DrawText("Congrats! You created your first window!", 190, 200, 20, LIGHTGRAY);

		// draw opSprings
		for (opSpring_t* spring = opSprings; spring != NULL; spring = spring->next) // do while we have a valid pointer, will be NULL at the end of the list
		{
			Vector2 screen1 = ConvertWorldToScreen(spring->body1->position);
			Vector2 screen2 = ConvertWorldToScreen(spring->body2->position);
			DrawLine((int)screen1.x, (int)screen1.y, (int)screen2.x, (int)screen2.y, YELLOW);
		}

		// draw opBodies
		for (opBody* body = opBodies; body != NULL; body = body->next) // do while we have a valid pointer, will be NULL at the end of the list
		{
			Vector2 screen = ConvertWorldToScreen(body->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(body->mass * 0.5f), body->color);
		}

		//draw contacts
		for (opContact_t* contact = contacts; contact != NULL; contact = contact->next) // do while we have a valid pointer, will be NULL at the end of the list
		{
			Vector2 screen = ConvertWorldToScreen(contact->body1->position);
			DrawCircle((int)screen.x, (int)screen.y, ConvertWorldToPixel(contact->body1->mass * 0.5f), RED);
		}

		DrawEditor(position);
		
		EndDrawing();
	}

	CloseWindow();
	free(opBodies);

	return 0;
}