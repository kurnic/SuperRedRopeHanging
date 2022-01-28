/**********************************************************************************************
*
*   raylib - Advance Game template
*
*   Gameplay Screen Functions Definitions (Init, Update, Draw, Unload)
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

bool started = false;
bool finished = false;
int phisycsCounter = 0;
int finishedCount = 0;

int gameScore = 0;

Vector2 ballPosition = { 280, 450};
Vector2 ballSpeed = {0, 0};

int mouseX, mouseY;

int auxRandom;

bool hooked;

int ceilingY = 50;
int floorY = 850;
int ceilingSpeed = 0;
int floorSpeed = 0;
int ceilingCounter = 750;
int floorCounter = 500;

int wallLeftX = 10;
int wallRightX = 890;
int wallLeftSpeed = 0;
int wallRightSpeed = 0;
int wallLeftCounter = 1000;
int wallRightCounter = 1000;

int limitBetweenWalls = 300;
int maxWallSpeed = 2;
int reactionTimeDecrease = 0;

//----------------------------------------------------------------------------------
// Gameplay Screen Functions Definition
//----------------------------------------------------------------------------------

// Gameplay Screen Initialization logic
void InitGameplayScreen(void)
{
    framesCounter = 0;
    finishScreen = 0;
    
    StopMusicStream(music1);
    PlayMusicStream(music2);
    
    score = 0;
    started = false;
    finished = false;
    finishedCount = 0;
    ballPosition.x = 270;
    ballPosition.y = 450;
    ballSpeed.x = 0;
    ballSpeed.y = 0;
    phisycsCounter = 0;
    
    mouseX = -1;
    mouseY = -1;
    hooked = false;
    auxRandom = GetRandomValue(5, 85);
    
    
    ceilingY = 50;
    floorY = 850;
    ceilingSpeed = 0;
    floorSpeed = 0;
    ceilingCounter = GetRandomValue(700, 800);
    floorCounter = GetRandomValue(400, 600);
    
    wallLeftX = 10;
    wallRightX = 530;
    wallLeftSpeed = 0;
    wallRightSpeed = 0;
    wallLeftCounter = GetRandomValue(900, 1250);
    wallRightCounter = GetRandomValue(900, 1250);
    
    limitBetweenWalls = 300;
    maxWallSpeed = 2;
    reactionTimeDecrease = 0;
}

// Gameplay Screen Update logic
void UpdateGameplayScreen(void)
{
    //TODO Screen shake function
    //TODO Add grabbable bonus
    //TODO That was close counter!
    
    mouseX = GetMouseX();
    mouseY = GetMouseY();
    
    //Hard reset
    if(IsKeyPressed(KEY_R)) {
        InitGameplayScreen();
    }
   
    if(!started) {
        //Small pause time showing tap to play
        if (IsGestureDetected(GESTURE_TAP))
        {
            started = true;
        }
    }
    else {
        if (!finished) {
            //Gameplay
            //Score
            score += ballPosition.y / 100;
            
            //Controls     
            if(IsMouseButtonDown(MOUSE_LEFT_BUTTON)) {
                if (mouseY < ceilingY || mouseY > floorY || mouseX < wallLeftX || mouseX > wallRightX) {
                    if (!hooked) {
                        PlaySound(fxGrab);
                    }
                    hooked = true;
                }
                else {
                    hooked = false;
                }
            }
            else {
                    hooked = false;
            }
            
            //Phisycs
                //Ball speed
            phisycsCounter += 1;
            if (phisycsCounter%2 == 0) {
                if (ballSpeed.y < 30) ballSpeed.y = ballSpeed.y + 1;
            }
            if (hooked) {
                if (ballSpeed.x > -30 || ballSpeed.x < 30) ballSpeed.x += (mouseX - ballPosition.x)/200;
                if (ballSpeed.y > -30 || ballSpeed.y < 30) ballSpeed.y += (mouseY - ballPosition.y)/200;
            }
            
                //Walls speed
                
            limitBetweenWalls = 300 - score/1000;
            maxWallSpeed = 2 + score/5000;
            reactionTimeDecrease = 5 * (score/6000);
                
            ceilingCounter -= 1;
            if (ceilingCounter < 1 || (ceilingSpeed < 0 && ceilingY < 51) || (ceilingSpeed > 0 && floorY - ceilingY < limitBetweenWalls)) {
                ceilingSpeed = GetRandomValue(-maxWallSpeed, maxWallSpeed);
                ceilingCounter = GetRandomValue(60 - reactionTimeDecrease, 240 - reactionTimeDecrease);
            }
            
            floorCounter -= 1;
            if (floorCounter < 1 || (floorSpeed > 0 && floorY > 849) || (floorSpeed < 0 && floorY - ceilingY < limitBetweenWalls)) {
                floorSpeed = GetRandomValue(-maxWallSpeed, maxWallSpeed);
                floorCounter = GetRandomValue(60 - reactionTimeDecrease, 240 - reactionTimeDecrease);
            }
            
            wallLeftCounter -= 1;
            if (wallLeftCounter < 1 || (wallLeftSpeed < 0 && wallLeftX < 10) || (wallLeftSpeed > 0 && wallRightX - wallLeftX < limitBetweenWalls)) {
                wallLeftSpeed = GetRandomValue(-maxWallSpeed, maxWallSpeed);
                wallLeftCounter = GetRandomValue(60 - reactionTimeDecrease, 240 - reactionTimeDecrease);
            }
            
            wallRightCounter -= 1;
            if (wallRightCounter < 1 || (wallRightSpeed > 0 && wallRightX > 530) || (wallRightSpeed < 0 && wallRightX - wallLeftX < limitBetweenWalls)) {
                wallRightSpeed = GetRandomValue(-maxWallSpeed, maxWallSpeed);
                wallRightCounter = GetRandomValue(60 - reactionTimeDecrease, 240 - reactionTimeDecrease);
            }

            //Movement
            ballPosition.x = ballPosition.x + ballSpeed.x;
            ballPosition.y = ballPosition.y + ballSpeed.y;
            
            ceilingY += ceilingSpeed;
            floorY += floorSpeed;
            wallLeftX += wallLeftSpeed;
            wallRightX += wallRightSpeed;
            
            //Death conditions
            if (ballPosition.y < ceilingY+10) 
            {
                if (!finished) {
                    PlaySound(fxCrash);
                }
                ballPosition.y = ceilingY+10;
                finished = true;
                hooked = false;
            }                
            if (ballPosition.y > floorY-10)
            {
                if (!finished) {
                    PlaySound(fxCrash);
                }
                ballPosition.y = floorY-10;
                finished = true;
                hooked = false;
            }
            if (ballPosition.x < wallLeftX+10) {
                if (!finished) {
                    PlaySound(fxCrash);
                }
                ballPosition.x = wallLeftX+10;
                finished = true;
                hooked = false;
            }
            if (ballPosition.x > wallRightX-10)
            {
                if (!finished) {
                    PlaySound(fxCrash);
                }
                ballPosition.x = wallRightX-10;
                finished = true;
                hooked = false;
            }
        }
        else {
            //Small pause time showing tap to end
            //Press enter or tap to change to ENDING screen (after 1.5 seconds to avoid taping by accident)
            if(finishedCount > 90) {
                if (IsKeyPressed(KEY_ENTER) || IsGestureDetected(GESTURE_TAP))
                {
                    finishScreen = 1;
                    PlaySound(fxMenu);
                }
            }
            else {
                finishedCount += 1;
            }
        }
    }

    
}

// Gameplay Screen Draw logic
void DrawGameplayScreen(void)
{
    //Background
    ClearBackground(WHITE);
    
    //Collision walls
        //Ceiling
    DrawRectangle(0, 0, 540, ceilingY, GRAY);
    DrawRectangle(0, ceilingY, 540, 2, BLACK);
    
        //Floor
    DrawRectangle(0, floorY, 540, 900-floorY, GRAY);
    DrawRectangle(0, floorY-2, 540, 2, BLACK);
    
    
        //Wall Left
    DrawRectangle(0, ceilingY, wallLeftX, floorY-ceilingY, GRAY);
    DrawRectangle(wallLeftX, ceilingY, 2, floorY-ceilingY, BLACK);
    
        //Wall Right
    DrawRectangle(wallRightX, ceilingY, 540-wallRightX, floorY-ceilingY, GRAY);
    DrawRectangle(wallRightX-2, ceilingY, 2, floorY-ceilingY, BLACK);
    
        //Screen borders
    DrawRectangle(0, 0, 540, 2, BLACK);
    DrawRectangle(0, 0, 2, 900, BLACK);
    DrawRectangle(538, 0, 2, 900, BLACK);
    DrawRectangle(0, 898, 540, 2, BLACK);
    
    //Texts
    if (started) {
        DrawText(TextFormat("Score: %i", score), 20, 10 , 36, BLACK);
        //DrawText(TextFormat("Limit: %i", limitBetweenWalls), 20, 30 , 36, BLACK);
        //DrawText(TextFormat("wallLeftX: %i", wallLeftX), 20, 50 , 36, BLACK);
        //DrawText(TextFormat("wallRightX: %i", wallRightX), 20, 70 , 36, BLACK);
        //DrawText(TextFormat("Dif: %i", wallRightX - wallLeftX), 20, 90 , 36, BLACK);
    }
    
    //Red rope
    if (hooked) {
        DrawLine(ballPosition.x, ballPosition.y, mouseX, mouseY, RED);
    }
    
    //Player
    DrawCircleV(ballPosition, 12, BLACK);
    DrawCircleV(ballPosition, 10, GOLD);
    
    //Start and end pause messages
    if (!started) {
        DrawText("TAP to START", 200, 20, 20, BLACK);
        DrawText("Press on gray areas to make an elastic rope.", 30, 120, 20, BLACK);
        DrawText("The rope attracts your yellow ball.", 84, 170, 20, BLACK);
        DrawText("Avoid the gray areas with your ball.", 80, 220, 20, BLACK);
        DrawText("After some time the gray walls will move.", 50, 270, 20, BLACK);
        DrawText("Stay low to score more points!", 100, 320, 20, BLACK);
        DrawText("TAP to START", 200, 865, 20, BLACK);
    }
    
    if (finished) {
        //Crash drawing
        DrawPoly(ballPosition,3,22,auxRandom,BLACK);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,22,auxRandom+90,BLACK);
        DrawPoly(ballPosition,3,22,auxRandom+180,BLACK);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,22,auxRandom+270,BLACK);
        DrawPoly(ballPosition,3,20,auxRandom,YELLOW);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,20,auxRandom+90,YELLOW);
        DrawPoly(ballPosition,3,20,auxRandom+180,YELLOW);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,20,auxRandom+270,YELLOW);
        DrawPoly(ballPosition,3,12,auxRandom,BLACK);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,12,auxRandom+90,BLACK);
        DrawPoly(ballPosition,3,12,auxRandom+180,BLACK);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,12,auxRandom+270,BLACK);
        DrawPoly(ballPosition,3,10,auxRandom,RED);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,10,auxRandom+90,RED);
        DrawPoly(ballPosition,3,10,auxRandom+180,RED);
        if(auxRandom%2 == 0)DrawPoly(ballPosition,3,10,auxRandom+270,RED);
        
        //Loser message
        DrawText("YOU CRASHED", 88, 386, 50, BLACK);
        DrawText("YOU CRASHED", 92, 390, 50, BLACK);
        DrawText("YOU CRASHED", 88, 390, 50, BLACK);
        DrawText("YOU CRASHED", 92, 386, 50, BLACK);
        DrawText("YOU CRASHED", 90, 388, 50, WHITE);
        
        //Message after 1.5 seconds
        if(finishedCount > 90) {
            DrawText("PRESS ENTER or TAP to", 140, 855, 20, BLACK);
            DrawText("JUMP to ENDING SCREEN", 140, 875, 20, BLACK);
        }
    }
}

// Gameplay Screen Unload logic
void UnloadGameplayScreen(void)
{

}

// Gameplay Screen should finish?
int FinishGameplayScreen(void)
{
    return finishScreen;
}