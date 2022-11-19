#pragma once
#include "Arduino.h"


#define PIN_M1 0	// Used for bootloader and Incremental-Switch, too. Is pulled up externally.
#define PIN_M2 2	// This will be our only servo output. Is pulled up externally.
#define PIN_M3 4 // Used for I2C
#define PIN_M4 5 // Used for I2C
#define PIN_M5 12
#define PIN_M6 13 // Re-used for PWM bin
#define PIN_MOT_A	14
#define PIN_MOT_B	15
#define PIN_SPARE	16

// Overdischarge protection
#define PIN_CHECK_BATT	A0

#define DEBUG_PRINTLN(a) Serial.println(a)
#define DEBUG_PRINT(a) Serial.print(a)

