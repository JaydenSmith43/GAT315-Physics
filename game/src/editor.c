#include "editor.h"
#include "body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool opEditorActive = true;
bool opEditorIntersect = false;
opEditorData_t opEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 776, 48 };
Vector2 anchor02 = { 792, 112 };

bool EditorBoxActive = true;
float MassMinValue = 0.0f;
float MassMaxValue = 0.0f;
float GravitationValue = 0.0f;
bool BodyTypeEditMode = false;
int BodyTypeActive = 0;
float BodyGravity = 0.0f;
float BodyDamping = 0.0f;

Texture2D cursorTexture;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/jungle/style_jungle.rgs");

    Image image = LoadImage("resources/reticle.png");
    cursorTexture = LoadTextureFromImage(image);
    UnloadImage(image);
    HideCursor();

    opEditorData.anchor01 = (Vector2){ 776, 48 };
    opEditorData.anchor02 = (Vector2){ 792, 112 };

    opEditorData.EditorBoxActive = false;
    opEditorData.GravitationValue = 0;
    opEditorData.MassMinValue = 0.1f;
    opEditorData.MassMaxValue = 1;
    opEditorData.BodyTypeEditMode = false;
    opEditorData.BodyTypeActive = 0;
    opEditorData.BodyGravity = 0.0f;
    opEditorData.BodyDamping = 0.0f;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { opEditorData.anchor01.x + 0, opEditorData.anchor01.y + 0, 304, 664 }, "Editor");
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 72, 120, 16 }, "Body Mass Min", NULL, & opEditorData.MassMinValue, 0, 5);
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 104, 120, 16 }, "Body Mass Max", NULL, & opEditorData.MassMaxValue, 0, 5);

        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 256, 120, 16 }, "Gravitation", NULL, & opEditorData.GravitationValue, 0, 100);

        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 136, 120, 16 }, "Body Gravity", NULL, & opEditorData.BodyGravity, 0, 100);
        GuiSliderBar((Rectangle) { opEditorData.anchor01.x + 120, opEditorData.anchor01.y + 168, 120, 16 }, "Body Damping", NULL, & opEditorData.BodyDamping, 0, 10);
        if (GuiDropdownBox((Rectangle) { opEditorData.anchor01.x + 32, opEditorData.anchor01.y + 200, 208, 16 }, "STATIC;KINEMATIC;DYNAMIC", & opEditorData.BodyTypeActive, opEditorData.BodyTypeEditMode)) opEditorData.BodyTypeEditMode = !opEditorData.BodyTypeEditMode;
    }
    GuiGroupBox((Rectangle) { opEditorData.anchor02.x + 0, opEditorData.anchor02.y + 0, 256, 176 }, "Body");

    DrawTexture(cursorTexture, position.x - cursorTexture.width / 2, position.y - cursorTexture.height / 2, WHITE);
    
    GuiUnlock();
}

opBody* GetBodyIntersect(opBody* bodies, Vector2 position)
{
    for (opBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
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