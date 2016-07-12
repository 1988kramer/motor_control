// DifferentialDrive
// by Andrew Kramer

#ifndef DifferentialDrive_h
#define DifferentialDrive_h

#include "Arduino.h"
#include <PositionControl.h>
#include <math.h>

class DifferentialDrive
{
public:
	DifferentialDrive(PositionControl*, PositionControl*, int, int);
	void drive(int speed, int radius);
	void drive(int speed, int radius, int distance);
	void update();
private:
	void updatePosition();
	void findSpeeds(int speed, int radius, int &leftSpeed, int &rightSpeed);
	int _wheelCirc; // circumference of wheels in millimeters
	int _wheelDistance; // distance between wheels in 
	int _xPosition, _yPosition;
	double _theta; // in radians
	double _degreesPerMillimeter;
	PositionControl *_leftWheel;
	PositionControl *_rightWheel;
};

#endif