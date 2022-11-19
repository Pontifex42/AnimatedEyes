//  Nilheim Mechatronics Simplified Eye Mechanism Code
//  X-axis joystick pin: PIN_ANALOG1
//  Y-axis joystick pin: PIN_ANALOG2
//  Trim potentiometer pin: PIN_ANALOG3
//  Button pin: 2

#include "PinConfig.h"
#include "Remote.h"
#include "Movement.h"

//#define DEBUG_INO
#ifndef DEBUG_INO
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif


void setup() 
{
    Serial.begin(115200);
    setupMovement();
    setupRemote();
}


void loop() 
{
    loopMovement();
    loopRemote();
    if (!RemoteXYIsConnected())
        return;

    int8_t xval;
    int8_t yval;
    GetEyeRollXY(&xval, &yval);
    DEBUG_PRINTLN("X:" + String(xval) + "   Y:" + String(yval));
    SetEyeXY(xval, yval);

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
