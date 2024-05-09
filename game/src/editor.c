#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool opEditorActive = true;
bool opEditorIntersect = false;
opEditorData_t opEditorData;

Rectangle editorRect;

Vector2 anchor01 = { 776, 48 };

bool EditorBoxActive = true;
float MassMinValue = 0.0f;
float MassMaxValue = 0.0f;
float GravitationValue = 0.0f;

void InitEditor()
{
    GuiLoadStyle("raygui/style/jungle/style_jungle.rgs");

    opEditorData.GravitationValue = 2;
    opEditorData.MassMinValue = 0.1f;
    opEditorData.MassMaxValue = 1;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor()
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 664 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 72, anchor01.y + 40, 120, 16 }, "Mass Min", NULL, & opEditorData.MassMinValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 72, anchor01.y + 72, 120, 16 }, "Mass Max", NULL, & opEditorData.MassMaxValue, 0, 10);
        GuiSliderBar((Rectangle) { anchor01.x + 72, anchor01.y + 104, 120, 16 }, "Gravitation", NULL, & opEditorData.GravitationValue, 0, 100);
    }
}
