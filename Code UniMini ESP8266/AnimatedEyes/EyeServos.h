#pragma once
#include <Servo.h>
#include "PinConfig.h"

// Servo timing is usually in a range of 1000us up to 2000us, but some servos act on a range 500us-2500us and some do more
#define PWM_MIN	500
#define PWM_MIDDLE 1500
#define PWM_MAX 2500

class EyeServo
{
public:
	EyeServo(int pin, int min = PWM_MIN, int max = PWM_MAX, int middle = -1); 	// set min is greater than max if you want to reverse directions
	void Setup();
	void ShutdownServo();
	void RestartServo();
	void Set(int pwm);
	void SetMin();
	void SetMiddle();
	void SetMax();
	void SetPercentage(int percent); // set in a range from -100 to 100
private:
	Servo myServo;
	int myPin;
	int myPWM;
	int myMin;
	int myMax;
	int myMiddle;
};

void SetupServos();
void LoopServos();
void RestartAllServos();
void ShutdownAllServos();

extern EyeServo ServoLeftLowerLid;
extern EyeServo ServoLeftUpperLid;
extern EyeServo ServoRightLowerLid;
extern EyeServo ServoRightUpperLid;
extern EyeServo ServoUpDown;
extern EyeServo ServoLeftRight;

// Left/Right is from viewers view, not from eyes view
#define MIN_LEFT_LOWER_LID 650 // down position
#define MID_LEFT_LOWER_LID 1700 // Middle position
#define MAX_LEFT_LOWER_LID 2130 // Up position

#define MIN_LEFT_UPPER_LID 1050 // down position
#define MID_LEFT_UPPER_LID 1270 // Middle position
#define MAX_LEFT_UPPER_LID 1920 // Up position

#define MIN_RIGHT_LOWER_LID 2350 // down
#define MID_RIGHT_LOWER_LID 1360 // middle
#define MAX_RIGHT_LOWER_LID 900	 // up

#define MIN_RIGHT_UPPER_LID 2150 // down
#define MID_RIGHT_UPPER_LID 1860 // middle
#define MAX_RIGHT_UPPER_LID 1000 // up

#define MIN_UPDOWN 1180 // Look down
#define MAX_UPDOWN 1750 // Look up

#define MIN_LEFTRIGHT 2120 // Look to "Right Lid"
#define MAX_LEFTRIGHT 1000 // Look to "Left Lid"
