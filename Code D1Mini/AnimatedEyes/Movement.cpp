#include "Movement.h"
#include "FaBoPWM_PCA9685.h"

//#define DEBUG_MOVEMENT
#ifndef DEBUG_MOVEMENT
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif


FaBoPWM faboPWM;

#define MIDDLE_POS 0

// servo ranges
void SetLeftLowerLid(int percentage)
{
#define MIN_LEFT_LOWER_LID 200
#define MAX_LEFT_LOWER_LID 470
    int mapval = map(percentage, -100, 100, MIN_LEFT_LOWER_LID, MAX_LEFT_LOWER_LID);
    //DEBUG_PRINTLN("MappedLL:" + String(mapval));
    faboPWM.set_channel_value(SRV_LEFT_LOWER_LID, mapval);
}

void SetLeftUpperLid(int percentage)
{
#define MIN_LEFT_UPPER_LID 500
#define MAX_LEFT_UPPER_LID 180
    int mapval = map(percentage, -100, 100, MIN_LEFT_UPPER_LID, MAX_LEFT_UPPER_LID);
    //DEBUG_PRINTLN("MappedLU:" + String(mapval));
    faboPWM.set_channel_value(SRV_LEFT_UPPER_LID, mapval);
}

void SetRightLowerLid(int percentage)
{
#define MIN_RIGHT_LOWER_LID 450
#define MAX_RIGHT_LOWER_LID 160
    int mapval = map(percentage, -100, 100, MIN_RIGHT_LOWER_LID, MAX_RIGHT_LOWER_LID);
    //DEBUG_PRINTLN("MappedRL:" + String(mapval));
    faboPWM.set_channel_value(SRV_RIGHT_LOWER_LID, mapval);
}

void SetRightUpperLid(int percentage)
{
#define MIN_RIGHT_UPPER_LID 190
#define MAX_RIGHT_UPPER_LID 420
    int mapval = map(percentage, -100, 100, MIN_RIGHT_UPPER_LID, MAX_RIGHT_UPPER_LID);
    //DEBUG_PRINTLN("MappedRU:" + String(mapval));
    faboPWM.set_channel_value(SRV_RIGHT_UPPER_LID, mapval);
}

void SetUpDown(int percentage)
{
#define MIN_UPDOWN 240
#define MAX_UPDOWN 390
    int mapval = map(percentage, -100, 100, MIN_UPDOWN, MAX_UPDOWN);
    //DEBUG_PRINTLN("MappedY:" + String(mapval));
    faboPWM.set_channel_value(SRV_UPDOWN, mapval);
}

void SetLeftRight(int percentage)
{
#define MIN_LEFTRIGHT 440
#define MAX_LEFTRIGHT 200
    int mapval = map(percentage, -100, 100, MIN_LEFTRIGHT, MAX_LEFTRIGHT);
    //DEBUG_PRINTLN("MappedX:" + String(mapval));
    faboPWM.set_channel_value(SRV_LEFTRIGHT, mapval);
}

void setupMovement()
{
    if (faboPWM.begin())
    {
        DEBUG_PRINTLN("Found PCA9685");
        faboPWM.init(PCA9685_DEFAULT_VALUE);
    }
    faboPWM.set_hz(50);
    
    SetLeftLowerLid(MIDDLE_POS);
    SetLeftUpperLid(MIDDLE_POS);
    SetUpDown(MIDDLE_POS);
    SetLeftRight(MIDDLE_POS);
    SetRightLowerLid(MIDDLE_POS);
    SetRightUpperLid(MIDDLE_POS);
}

void loopMovement()
{

}

void SetEyeXY(int8_t x, int8_t y)
{
    SetLeftRight(x);
    SetUpDown(y);
}

void SetEyeLid(int8_t open, int8_t direction, int eyes)
{
#define LOWER_MIDDLE -48
    int openness = map(open, -100, 100, 0, 80); // degrees opened lid
    int directed = map(direction, -100, 100, -50, 50); // degrees up or down opened
    DEBUG_PRINTLN("Opened: " + String(openness) + "   Directed:" + String(directed));
    int upperangle = openness + direction;
    if (upperangle < -100)
        upperangle = -100;
    else if (upperangle > 100)
        upperangle = 100;

    int lowerangle = openness - direction + LOWER_MIDDLE;
    if (lowerangle < -100)
        lowerangle = -100;
    else if (lowerangle > 100)
        lowerangle = 100;

    if (eyes & USE_LEFT_EYE)
    {
        SetLeftLowerLid(lowerangle);
        SetLeftUpperLid(upperangle);
    }
    if (eyes & USE_RIGHT_EYE)
    {
        SetRightLowerLid(lowerangle);
        SetRightUpperLid(upperangle);
    }
}

void DoBlink(int eyes)
{
    if (eyes == 0)
        return;
        
    SetEyeLid(-100, 0, eyes);
    delay(220);
}

