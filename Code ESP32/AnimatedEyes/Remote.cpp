#include "Remote.h"

// #define DEBUG_REMOTE
#ifndef DEBUG_REMOTE
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif

//////////////////////////////////////////////
//        RemoteXY include library          //
//////////////////////////////////////////////

// RemoteXY select connection mode and include library 
#define REMOTEXY_MODE__ESP32CORE_BLE
#include <BLEDevice.h>

#include <RemoteXY.h>

// RemoteXY connection settings 
#define REMOTEXY_BLUETOOTH_NAME "AnimatedEyes"


// RemoteXY configurate  
#pragma pack(push, 1)
uint8_t RemoteXY_CONF[] =   // 62 bytes
{ 255,7,0,0,0,55,0,16,21,1,1,0,24,4,16,16,120,31,0,4,
32,1,0,8,49,2,26,5,0,7,48,49,49,9,130,6,4,32,54,0,
8,48,2,26,1,0,15,29,12,12,176,31,0,1,0,37,29,12,12,165,
31,0 };

// this structure defines all the variables and events of your control interface 
struct {

    // input variables
    uint8_t Blink; // =1 if button pressed, else =0 
    int8_t LidOpen; // =-100..100 slider position 
    int8_t EyeRoll_x; // from -100 to 100  
    int8_t EyeRoll_y; // from -100 to 100  
    int8_t Direction; // =-100..100 slider position 
    uint8_t BlinkLeft; // =1 if button pressed, else =0 
    uint8_t BlinkRight; // =1 if button pressed, else =0 

      // other variable
    uint8_t connect_flag;  // =1 if wire connected, else =0 

} RemoteXY;
#pragma pack(pop)

/////////////////////////////////////////////
//           END RemoteXY include          //
/////////////////////////////////////////////


void setupRemote()
{
    RemoteXY_Init();
}

void loopRemote()
{
    RemoteXY_Handler();
}

int GetBlink()
{
    int ret = 0;
    if (RemoteXY.Blink == 1)
        return USE_LEFT_EYE | USE_RIGHT_EYE;
    
    if (RemoteXY.BlinkLeft == 1)
        return USE_LEFT_EYE;

    if (RemoteXY.BlinkRight == 1)
        return USE_RIGHT_EYE;
    return 0;
}

void GetEyeRollXY(int8_t* x, int8_t* y)
{
    *x = RemoteXY.EyeRoll_x;
    *y = RemoteXY.EyeRoll_y;
}

int GetLidOpen()
{
    return RemoteXY.LidOpen;
}

int GetLidDirection()
{
    return RemoteXY.Direction;
}

bool RemoteXYIsConnected()
{
    return (RemoteXY.connect_flag == true);
}
