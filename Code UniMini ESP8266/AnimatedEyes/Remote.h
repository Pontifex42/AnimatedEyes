#pragma once
#include "PinConfig.h"

void SetupRemote();
void LoopRemote();
bool RemoteXYIsConnected();

#define USE_LEFT_EYE 0x01
#define USE_RIGHT_EYE 0x02
int GetBlink();
void GetEyeRollXY(int8_t* x, int8_t* y);
int GetLidOpen();
int GetLidDirection();

