#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"


#define EDITOR_DATA(data)
bool opEditorActive = true;
bool opEditorIntersect = false;
opEditorData_t opEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 776, 48 };

bool EditorBoxActive = true;
float MassValue = 0.0f;
float BodyDampingValue = 0.0f;
bool BodyTypeEditMode = false;
int BodyTypeActive = 0;
float GravityScaleValue = 0.0f;
float StiffnessValue = 0.0f;
float RestitutionValue = 0.0f;
float GravityValue = 0.0f;
float GravitationValue = 0.0f;
float TimestepValue = 0.0f;
bool ResetPressed = false;
bool SimulateToggleActive = true;

Texture2D cursorTexture;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/jungle/style_jungle.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    opEditorData.anchor01 = (Vector2){ 744, 24 };

    opEditorData.EditorBoxActive = false;
    opEditorData.Mass = 0.1f;
    opEditorData.BodyDamping = 0.0f;
    opEditorData.BodyTypeEditMode = false;
    opEditorData.BodyTypeActive = 0;
    opEditorData.BodyGravityScale = 0.0f;
    opEditorData.Restitution = 0.0f;
    opEditorData.Stiffness = 0.0f;

    opEditorData.Gravity = 0.0f;
    opEditorData.Gravitation = 0.0f;
    opEditorData.Timestep = 0.0f;

    opEditorData.ResetPressed = false;
    opEditorData.SimulateToggleActive = true;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 312, 512 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 128, anchor01.y + 120, 120, 16 }, "Mass", NULL, & opEditorData.Mass, 0.2f, 5);
        GuiGroupBox((Rectangle) { anchor01.x + 24, anchor01.y + 48, 264, 232 }, "Body");
        GuiGroupBox((Rectangle) { anchor01.x + 24, anchor01.y + 312, 264, 112 }, "World");
        GuiSliderBar((Rectangle) { anchor01.x + 128, anchor01.y + 144, 120, 16 }, "Damping", NULL, & opEditorData.BodyDamping, 0, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 128, anchor01.y + 168, 120, 16 }, "Gravity Scale", NULL, & opEditorData.BodyGravityScale, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 128, anchor01.y + 192, 120, 16 }, "Stiffness (k)", NULL, & opEditorData.Stiffness, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 128, anchor01.y + 216, 120, 16 }, "Restitution", NULL, & opEditorData.Restitution, 0, 100);
        GuiSlider((Rectangle) { anchor01.x + 120, anchor01.y + 328, 128, 16 }, "Gravity", NULL, & opEditorData.Gravity, 0, 100);
        GuiSlider((Rectangle) { anchor01.x + 120, anchor01.y + 352, 128, 16 }, "Gravitation", NULL, & opEditorData.Gravitation, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 120, anchor01.y + 376, 128, 16 }, "Timestep", NULL, & opEditorData.Timestep, 0, 100);
        ResetPressed = GuiButton((Rectangle) { anchor01.x + 24, anchor01.y + 456, 120, 24 }, "Reset");
        GuiToggle((Rectangle) { anchor01.x + 168, anchor01.y + 456, 120, 24 }, "Simulate", & opEditorData.SimulateToggleActive);
        if (GuiDropdownBox((Rectangle) { anchor01.x + 64, anchor01.y + 64, 184, 32 }, "STATIC;KINEMATIC;DYNAMIC", & opEditorData.BodyTypeActive, opEditorData.BodyTypeEditMode)) opEditorData.BodyTypeEditMode = !opEditorData.BodyTypeEditMode;
    }

    /*
        EditorBoxActive = !GuiWindowBox((Rectangle) { opEditorData.anchor01.x + 0, opEditorData.anchor01.y + 0, 304, 664 }, "Editor");
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 72, 120, 16 }, "Body Mass Min", NULL, & opEditorData.MassMinValue, 0, 5);
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 104, 120, 16 }, "Body Mass Max", NULL, & opEditorData.MassMaxValue, 0, 5);

        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 256, 120, 16 }, "Gravitation", NULL, & opEditorData.GravitationValue, 0, 100);

        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 136, 120, 16 }, "Body Gravity", NULL, & opEditorData.BodyGravity, 0, 100);
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 168, 120, 16 }, "Body Damping", NULL, & opEditorData.BodyDamping, 0, 10);
        if (GuiDropdownBox((Rectangle) { opEditorData.anchor01.x + 32, opEditorData.anchor01.y + 200, 208, 16 }, "STATIC;KINEMATIC;DYNAMIC", & opEditorData.BodyTypeActive, opEditorData.BodyTypeEditMode)) opEditorData.BodyTypeEditMode = !opEditorData.BodyTypeEditMode;
    */

    DrawTexture(cursorTexture, position.x - cursorTexture.width / 2, position.y - cursorTexture.height / 2, WHITE);
    
    GuiUnlock();
}

opBody* GetBodyIntersect(opBody* bodies, Vector2 position)
{
    for (opBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(opBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}