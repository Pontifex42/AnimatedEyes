#pragma once
#include "Arduino.h"

// I2C for PCA9685
#define PIN_SDA 21
#define PIN_SCL 22

// Servo identities
#define SRV_LEFT_LOWER_LID 0
#define SRV_LEFT_UPPER_LID 1
#define SRV_UPDOWN 2
#define SRV_LEFTRIGHT 3
#define SRV_RIGHT_UPPER_LID 4
#define SRV_RIGHT_LOWER_LID 5

#define DEBUG_PRINTLN(a) Serial.println(a)
#define DEBUG_PRINT(a) Serial.print(a)

