#pragma once
#include "PinConfig.h"
#include "Remote.h"

void SetupMovement();
void LoopMovement();

void SetEyeBall(int8_t x, int8_t y);
void SetEyeLid(int8_t open, int8_t direction, int eyes = (USE_LEFT_EYE | USE_RIGHT_EYE));
void DoBlink(int eyes = (USE_LEFT_EYE | USE_RIGHT_EYE));

