#include "PinConfig.h"
#include "Remote.h"
#include "Movement.h"
#include "BatteryProtect.h"
#include "EyeServos.h"

//#define DEBUG_INO
#ifndef DEBUG_INO
#undef DEBUG_PRINTLN
#undef DEBUG_PRINT
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif

bool HandleBatteryAlarm()
{
    if (!GetBatteryAlarmState())
        return false;

    static bool AlarmWasActive = false;

    bool AlarmIsActive = GetBatteryAlarmState();
    if (AlarmWasActive && !AlarmIsActive)
    {	// return to normal state
        AlarmWasActive = false;
        DEBUG_PRINTLN("Battery alarm ends.");

        RestartAllServos();
    }
    else if (!AlarmWasActive && AlarmIsActive)
    {	// Go to power save mode.
        AlarmWasActive = true;
        DEBUG_PRINTLN("Battery alarm!");

        ShutdownAllServos();
    }

    return AlarmIsActive;
}

void setup() 
{
    Serial.begin(115200);
    DEBUG_PRINTLN(""); // ESP sends garbage using 74880 baud at boot.
    SetupBatteryProtect();
    SetupServos();
    SetupMovement();
    SetupRemote();
    DEBUG_PRINTLN("Setup done");
}


void loop() 
{
    LoopBatteryProtect();
    /* ToDo: enable Battery protect
    if (HandleBatteryAlarm())
        return;
    */
    LoopServos();
    LoopRemote();
    if (!RemoteXYIsConnected())
        return;

    LoopMovement();
}
