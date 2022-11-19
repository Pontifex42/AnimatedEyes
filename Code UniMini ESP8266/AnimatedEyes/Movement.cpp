#include "Movement.h"
#include "EyeServos.h"
#include "Remote.h"

//#define DEBUG_MOVEMENT

#ifndef DEBUG_MOVEMENT
#undef DEBUG_PRINTLN
#undef DEBUG_PRINT
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif


#define LEFT_LOWER_LID_UP       MAX_LEFT_LOWER_LID
#define LEFT_LOWER_LID_SLOT     MID_LEFT_LOWER_LID
#define LEFT_LOWER_LID_DOWN     MIN_LEFT_LOWER_LID

#define LEFT_UPPER_LID_UP       MAX_LEFT_UPPER_LID
#define LEFT_UPPER_LID_SLOT     MID_LEFT_UPPER_LID
#define LEFT_UPPER_LID_DOWN     MIN_LEFT_UPPER_LID

#define RIGHT_LOWER_LID_UP      MIN_RIGHT_LOWER_LID
#define RIGHT_LOWER_LID_SLOT    MID_RIGHT_LOWER_LID
#define RIGHT_LOWER_LID_DOWN    MAX_RIGHT_LOWER_LID

#define RIGHT_UPPER_LID_UP      MAX_RIGHT_UPPER_LID
#define RIGHT_UPPER_LID_SLOT    MID_RIGHT_UPPER_LID
#define RIGHT_UPPER_LID_DOWN    MIN_RIGHT_UPPER_LID


void SetEyeBall(int8_t x, int8_t y)
{
    ServoLeftRight.SetPercentage(x);
    ServoUpDown.SetPercentage(y);
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
        ServoLeftLowerLid.SetPercentage(lowerangle);
        ServoLeftUpperLid.SetPercentage(upperangle);
    }
    if (eyes & USE_RIGHT_EYE)
    {
        ServoRightLowerLid.SetPercentage(lowerangle);
        ServoRightUpperLid.SetPercentage(upperangle);
    }
}

void DoBlink(int eyes)
{
    if (eyes == 0)
        return;
    if (eyes & USE_LEFT_EYE)
    {
        ServoLeftLowerLid.Set(LEFT_LOWER_LID_SLOT);
        ServoLeftUpperLid.Set(LEFT_UPPER_LID_SLOT);
    }
    if (eyes & USE_RIGHT_EYE)
    {
        ServoRightLowerLid.Set(MID_RIGHT_LOWER_LID);
        ServoRightUpperLid.Set(MID_RIGHT_UPPER_LID);
    }
    delay(220);
}

void SetupMovement()
{
}

void LoopMovement()
{
    int8_t xval, yval;
    GetEyeRollXY(&xval, &yval);
   // DEBUG_PRINTLN("X:" + String(xval) + "   Y:" + String(yval));
    SetEyeBall(xval, yval);

    int b = GetBlink();
    if (b != 0)
        DoBlink(b);
    else
    {
        int8_t open = GetLidOpen();
        int8_t direction = GetLidDirection();
        DEBUG_PRINTLN("LidOpen:" + String(open) + "   LidDir:" + String(direction));
        SetEyeLid(open, direction);
    }
}