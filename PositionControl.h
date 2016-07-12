// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control 

#ifndef PositionControl_h
#define PositionControl_h

#include"Arduino.h"
#include<SpeedControl.h>

class PositionControl
{
public:
	PositionControl(SpeedControl *speedControl);
	void rotate(int degrees, int speed); // in degrees
	void setSpeed(int speed); // in degrees/sec
	int getDistance(); // returns total distance rotated in degrees
	void setKP(double kP);
	void adjustPWM();
private:
	void constrainSpeed(int &newSpeed);
	SpeedControl *_speedControl;
	int _error, _speed;
	long _distance;
	double _kP;
	bool _positioning;
};

#endif
