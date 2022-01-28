/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Title Screen Functions Definitions (Init, Update, Draw, Unload)
*
*   Copyright (c) 2014-2022 Ramon Santamaria (@raysan5)
*
*   This software is provided "as-is", without any express or implied warranty. In no event
*   will the authors be held liable for any damages arising from the use of this software.
*
*   Permission is granted to anyone to use this software for any purpose, including commercial
*   applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*     1. The origin of this software must not be misrepresented; you must not claim that you
*     wrote the original software. If you use this software in a product, an acknowledgment
*     in the product documentation would be appreciated but is not required.
*
*     2. Altered source versions must be plainly marked as such, and must not be misrepresented
*     as being the original software.
*
*     3. This notice may not be removed or altered from any source distribution.
*
**********************************************************************************************/

#include "raylib.h"
#include "screens.h"

//----------------------------------------------------------------------------------
// Module Variables Definition (local)
//----------------------------------------------------------------------------------
static int framesCounter = 0;
static int finishScreen = 0;

bool bgChange = true;
Color bgColor = WHITE;

//----------------------------------------------------------------------------------
// Title Screen Functions Definition
//----------------------------------------------------------------------------------

// Title Screen Initialization logic
void InitTitleScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
}

// Title Screen Update logic
void UpdateTitleScreen(void)
{
    // Press enter or tap to change to GAMEPLAY screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        PlaySound(fxMenu);
        //finishScreen = 1;   // OPTIONS
        finishScreen = 2;   // GAMEPLAY
    }
    
    //BG animation
    if(bgChange) {
        if(bgColor.r > 150) {
            bgColor.r = bgColor.r - 2;
            bgColor.g = bgColor.g - 2;
            bgColor.b = bgColor.b - 2;
        }
        else bgChange = !bgChange;
    }
    else {
        if(bgColor.r < 255) {
            bgColor.r = bgColor.r + 2;
            bgColor.g = bgColor.g + 2;
            bgColor.b = bgColor.b + 2;
        }
        else bgChange = !bgChange;
    }
}

// Title Screen Draw logic
void DrawTitleScreen(void)
{
    ClearBackground(bgColor);
    
    DrawRectangle(0, 0, 540, 2, BLACK);
    DrawRectangle(0, 898, 540, 2, BLACK);
    
    DrawRectangle(0, 0, 2, 900, BLACK);
    DrawRectangle(538, 0, 2, 900, BLACK);
    
    DrawText("SUPER RED ROPE", 38, 366, 50, BLACK);
    DrawText("SUPER RED ROPE", 42, 370, 50, BLACK);
    DrawText("SUPER RED ROPE", 38, 370, 50, BLACK);
    DrawText("SUPER RED ROPE", 42, 366, 50, BLACK);
    DrawText("SUPER RED ROPE", 40, 368, 50, RED);
    
    DrawText("HANGING", 85, 428, 80, BLACK);
    DrawText("HANGING", 89, 432, 80, BLACK);
    DrawText("HANGING", 85, 432, 80, BLACK);
    DrawText("HANGING", 89, 428, 80, BLACK);
    DrawText("HANGING", 87, 430, 80, RED);
    
    DrawText("PRESS ENTER or TAP to START", 95, 550, 20, BLACK);
}

// Title Screen Unload logic
void UnloadTitleScreen(void)
{

}

// Title Screen should finish?
int FinishTitleScreen(void)
{
    return finishScreen;
}