/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Ending Screen Functions Definitions (Init, Update, Draw, Unload)
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

int finalScore = 0;

bool bgChangeEnd = true;
Color bgColorEnd = BLACK;

//----------------------------------------------------------------------------------
// Ending Screen Functions Definition
//----------------------------------------------------------------------------------

int numPlaces (int n) {
    if (n < 10) return 1;
    if (n < 100) return 2;
    if (n < 1000) return 3;
    if (n < 10000) return 4;
    if (n < 100000) return 5;
    if (n < 1000000) return 6;
    if (n < 10000000) return 7;
    if (n < 100000000) return 8;
    if (n < 1000000000) return 9;
    /*      2147483647 is 2^31-1 - add more ifs as needed
       and adjust this final return as well. */
    return 10;
}


// Ending Screen Initialization logic
void InitEndingScreen(int score)
{
    framesCounter = 0;
    finishScreen = 0;
    
    finalScore = score;
}

// Ending Screen Update logic
void UpdateEndingScreen(void)
{
    // Press enter or tap to return to TITLE screen
    if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
    {
        finishScreen = 1;
        PlaySound(fxMenu);
    }
    
    //BG animation
    if(bgChangeEnd) {
        if(bgColorEnd.r > 0) {
            bgColorEnd.r = bgColorEnd.r - 2;
            bgColorEnd.g = bgColorEnd.g - 2;
            bgColorEnd.b = bgColorEnd.b - 2;
        }
        else bgChangeEnd = !bgChangeEnd;
    }
    else {
        if(bgColorEnd.r < 150) {
            bgColorEnd.r = bgColorEnd.r + 2;
            bgColorEnd.g = bgColorEnd.g + 2;
            bgColorEnd.b = bgColorEnd.b + 2;
        }
        else bgChangeEnd = !bgChangeEnd;
    }
    
    StopMusicStream(music2);
    PlayMusicStream(music1);
}

// Ending Screen Draw logic
void DrawEndingScreen(void)
{
    ClearBackground(bgColorEnd);
    
    DrawRectangle(0, 0, 540, 2, BLACK);
    DrawRectangle(0, 898, 540, 2, BLACK);
    
    DrawRectangle(0, 0, 2, 900, BLACK);
    DrawRectangle(538, 0, 2, 900, BLACK);
    
    DrawText("SUPER RED ROPE", 38, 86, 50, BLACK);
    DrawText("SUPER RED ROPE", 42, 90, 50, BLACK);
    DrawText("SUPER RED ROPE", 38, 90, 50, BLACK);
    DrawText("SUPER RED ROPE", 42, 86, 50, BLACK);
    DrawText("SUPER RED ROPE", 40, 88, 50, RED);
    
    DrawText("HANGING", 85, 158, 80, BLACK);
    DrawText("HANGING", 89, 152, 80, BLACK);
    DrawText("HANGING", 85, 152, 80, BLACK);
    DrawText("HANGING", 89, 158, 80, BLACK);
    DrawText("HANGING", 87, 155, 80, RED);
    
    DrawText("Score", 85, 358, 120, BLACK);
    DrawText("Score", 85, 362, 120, BLACK);
    DrawText("Score", 89, 358, 120, BLACK);
    DrawText("Score", 89, 362, 120, BLACK);
    DrawText("Score", 87, 360, 120, WHITE);
    
    DrawText(TextFormat("%i", finalScore), 258 - (29 * numPlaces(finalScore)), 478, 120, BLACK);
    DrawText(TextFormat("%i", finalScore), 258 - (29 * numPlaces(finalScore)), 482, 120, BLACK);
    DrawText(TextFormat("%i", finalScore), 262 - (29 * numPlaces(finalScore)), 478, 120, BLACK);
    DrawText(TextFormat("%i", finalScore), 262 - (29 * numPlaces(finalScore)), 482, 120, BLACK);
    DrawText(TextFormat("%i", finalScore), 260 - (29 * numPlaces(finalScore)), 480, 120, WHITE);
    
    DrawText("PRESS ENTER or TAP to RESTART", 85, 750, 20, WHITE);
}

// Ending Screen Unload logic
void UnloadEndingScreen(void)
{

}

// Ending Screen should finish?
int FinishEndingScreen(void)
{
    return finishScreen;
}