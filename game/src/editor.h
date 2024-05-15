#pragma once
#include "raylib.h"

typedef struct opEditorData
{
	Vector2 anchor01;
	Vector2 anchor02;

	bool EditorBoxActive;
	float MassMinValue;
	float MassMaxValue;
	float GravitationValue;
	bool BodyTypeEditMode;
	int BodyTypeActive;
	float BodyGravity;
	float BodyDamping;
} opEditorData_t;

extern opEditorData_t opEditorData;

extern bool opEditorActive;
extern bool opEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 position);
void DrawEditor(Vector2 position);

struct opBody* GetBodyIntersect(struct opBody* bodies, Vector2 position);
void DrawLineBodyToPosition(struct opBody* body, Vector2 position);