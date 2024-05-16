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
	opGravity = (Vector2){ 0, 0 }; //0,30
	int selection = 0;

	// Game Loop
	while (!WindowShouldClose())
	{
		// Update
		float dt = GetFrameTime();
		float fps = (float)GetFPS();

		if (IsKeyPressed('W'))
		{
			selection++;

			if (selection == 3)
			{
				selection = 0;
			}
		}
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
			switch (selection)
			{
				case 0:
					for (int i = 0; i < 1; i++)
					{
						opBody* body = CreateBody(ConvertScreenToWorld(position), opEditorData.MassMinValue, opEditorData.BodyTypeActive);
						body->damping = opEditorData.BodyDamping; //opEditorData.BodyDamping //0,10
						body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
						body->gravityScale = opEditorData.BodyGravity;// .GravityScaleValue 0,10
						body->restitution = 0.8f; //bounciness
						AddBody(body);
						//ApplyForce(body, (Vector2) { GetRandomFloatValue(-200, 200), GetRandomFloatValue(-500, -1000) }, FM_VELOCITY);//
					}
					break;
				case 1:
					//for (int i = 0; i < 100; i++)
					//{
					//	opBody* body = CreateBody();
					//	body->position = ConvertScreenToWorld(position);
					//	body->mass = GetRandomFloatValue(opEditorData.MassMinValue, opEditorData.MassMaxValue);
					//	body->inverseMass = 1 / body->mass;
					//	body->type = BT_DYNAMIC;
					//	body->damping = 0.99f;
					//	body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
					//	body->gravityScale = 20;//
					//	Vector2 force = Vector2Scale(GetVector2FromAngle(GetRandomFloatValue(0, 360) * DEG2RAD), GetRandomFloatValue(10, 20));
					//	ApplyForce(body, force, FM_IMPULSE);//	
					//	AddBody(body);
					//}
					break;
				//case 2:
				//	angle = GetRandomFloatValue(0, 360);
				//	for (int i = 0; i < 100; i++)
				//	{
				//		opBody* body = CreateBody();
				//		body->position = ConvertScreenToWorld(position);
				//		body->mass = GetRandomFloatValue(opEditorData.MassMinValue, opEditorData.MassMaxValue);
				//		body->inverseMass = 1 / body->mass;
				//		body->type = BT_DYNAMIC;
				//		body->damping = 0.99f;
				//		body->color = (Color){ GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
				//		body->gravityScale = 20;//
				//		Vector2 force = Vector2Scale(GetVector2FromAngle(angle + GetRandomFloatValue(-30, 30) * DEG2RAD), GetRandomFloatValue(10, 20));
				//		ApplyForce(body, force, FM_IMPULSE);//	
				//	}
				//	break;
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

		// apply force opBodies
		ApplyGravitation(opBodies, opEditorData.GravitationValue);
		ApplySpringForce(opSprings);

		// update opBodies
		for (opBody* body = opBodies; body != NULL; body = body->next) //while not null
		{
			Step(body, dt);
		}

		// collision
		opContact_t* contacts = NULL;
		CreateContacts(opBodies, &contacts);
		SeparateContacts(contacts);
		ResolveContacts(contacts);

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