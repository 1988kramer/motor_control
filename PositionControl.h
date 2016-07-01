// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control 

#ifndef PositionControl_h
#define PositionControl_h

#include"Arduino.h"

class PositionControl
{
public:
	PositionControl(SpeedControl speedControl);
	void rotate(int degrees, int speed); // in degrees
	void setSpeed(int speed); // in degrees/sec
	int getDistance(); // returns total distance rotated in degrees
private:
	SpeedControl _speedControl;
	long _distance;
};

#endif