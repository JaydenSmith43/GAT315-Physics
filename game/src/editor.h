#pragma once
#include "raylib.h"

typedef struct opEditorData
{
	float MassMinValue;
	float MassMaxValue;
	float GravitationValue;
} opEditorData_t;

extern opEditorData_t opEditorData;

extern bool opEditorActive;
extern bool opEditorIntersect;

void InitEditor();
void UpdateEditor(Vector2 mousePosition);
void DrawEditor();