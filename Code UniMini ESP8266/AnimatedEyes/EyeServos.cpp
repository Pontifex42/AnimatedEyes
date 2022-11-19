#include "EyeServos.h"
#include "PinConfig.h"

//#define DEBUG_EYESERVOS

#ifndef DEBUG_EYESERVOS
#undef DEBUG_PRINTLN
#undef DEBUG_PRINT
#define DEBUG_PRINTLN(a)
#define DEBUG_PRINT(a)
#endif


// Servo identities
#define PIN_SRV_LEFT_LOWER_LID	PIN_M1
#define PIN_SRV_LEFT_UPPER_LID	PIN_M2
#define PIN_SRV_UPDOWN			PIN_M3
#define PIN_SRV_LEFTRIGHT		PIN_M4
#define PIN_SRV_RIGHT_UPPER_LID PIN_M5
#define PIN_SRV_RIGHT_LOWER_LID PIN_M6

EyeServo ServoLeftLowerLid(PIN_SRV_LEFT_LOWER_LID, MIN_LEFT_LOWER_LID, MAX_LEFT_LOWER_LID, MID_LEFT_LOWER_LID);
EyeServo ServoLeftUpperLid(PIN_SRV_LEFT_UPPER_LID, MIN_LEFT_UPPER_LID, MAX_LEFT_UPPER_LID, MID_LEFT_UPPER_LID);
EyeServo ServoRightLowerLid(PIN_SRV_RIGHT_LOWER_LID, MIN_RIGHT_LOWER_LID, MAX_RIGHT_LOWER_LID, MID_RIGHT_LOWER_LID);
EyeServo ServoRightUpperLid(PIN_SRV_RIGHT_UPPER_LID, MIN_RIGHT_UPPER_LID, MAX_RIGHT_UPPER_LID, MID_RIGHT_UPPER_LID);
EyeServo ServoUpDown(PIN_SRV_UPDOWN, MIN_UPDOWN, MAX_UPDOWN);
EyeServo ServoLeftRight(PIN_SRV_LEFTRIGHT, MIN_LEFTRIGHT, MAX_LEFTRIGHT);

EyeServo::EyeServo(int pin, int min, int max, int middle)
{
	myPin = pin;

	myMin = min; // it is allowed that min is greater than max
	myMax = max;
	if(middle == -1)
		myMiddle = (myMin + myMax) / 2;
	else
		myMiddle = middle;

	myPWM = myMiddle;
}

void EyeServo::Setup()
{
	RestartServo();
}

void EyeServo::ShutdownServo()
{
	myServo.detach();
}

void EyeServo::RestartServo()
{
	if (myMin < myMax)
		myServo.attach(myPin, myMin, myMax, myPWM);
	else
		myServo.attach(myPin, myMax, myMin, myPWM);
}

void EyeServo::Set(int pwm)
{
	if (pwm == myPWM)
		return;

	if (myMin < myMax)
	{
		if (pwm < myMin)
			pwm = myMin;
		else if (pwm > myMax)
			pwm = myMax;
	}
	else // (myMin > myMax)
	{
		if (pwm > myMin)
			pwm = myMin;
		else if (pwm < myMax)
			pwm = myMax;
	}

	myServo.writeMicroseconds(pwm);
	myPWM = pwm;
}

void EyeServo::SetPercentage(int percent)
{
	int mapval = map(percent, -100, 100, myMin, myMax);
	Set(mapval);
}

void EyeServo::SetMin()
{
	Set(myMin);
}

void EyeServo::SetMiddle()
{
	Set(myMiddle);
}

void EyeServo::SetMax()
{
	Set(myMax);
}

void SetupServos()
{
	ServoLeftLowerLid.Setup();
	ServoLeftUpperLid.Setup();
	ServoRightLowerLid.Setup();
	ServoRightUpperLid.Setup();
	ServoUpDown.Setup();
	ServoLeftRight.Setup();
}

void LoopServos()
{

}

void ShutdownAllServos()
{
	ServoLeftLowerLid.ShutdownServo();
	ServoLeftUpperLid.ShutdownServo();
	ServoRightLowerLid.ShutdownServo();
	ServoRightUpperLid.ShutdownServo();
	ServoUpDown.ShutdownServo();
	ServoLeftRight.ShutdownServo();
}

void RestartAllServos()
{
	ServoLeftLowerLid.RestartServo();
	ServoLeftUpperLid.RestartServo();
	ServoRightLowerLid.RestartServo();
	ServoRightUpperLid.RestartServo();
	ServoUpDown.RestartServo();
	ServoLeftRight.RestartServo();
}