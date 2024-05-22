#pragma once
#include "raylib.h"

typedef struct opEditorData
{
	Vector2 anchor01;

	bool EditorBoxActive;
    float Mass;
    float BodyDamping;
    bool BodyTypeEditMode;
    int BodyTypeActive;
    float BodyGravityScale;
    float Stiffness;
    float Restitution;
    float Gravity;
    float Gravitation;
    float Timestep;
    bool ResetPressed;
    bool SimulatePressed;
} opEditorData_t;

extern opEditorData_t opEditorData;

extern bool opEditorActive;
extern bool opEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct opBody* GetBodyIntersect(struct opBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct opBody* body, Vector2 position);