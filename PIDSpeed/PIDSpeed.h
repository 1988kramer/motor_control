// PIDSpeed
// by Andrew Kramer

// controls motor speed using PID control loop
// based on Brett Beauregard's PID library

#ifndef PIDSpeed_h
#define PIDSpeed_h

#include "Arduino.h"
#include<Motor.h>

class PIDSpeed
{
public:
	void setSpeed();
private:
	void adjustPWM();
	int _encoderA, _encoderB;
	Motor _theMotor;
}

#endif