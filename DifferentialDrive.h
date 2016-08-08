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
	void drive(int translational, double angular);
	void drive(int translational, double angular, int distance);
	void getPosition(double &x, double &y, double &theta);
	void resetPosition();
	void update();
private:
	void updatePosition();
	void findSpeeds(int translational, double angular, 
					int &leftSpeed, int &rightSpeed);
	int _wheelCirc; // circumference of wheels in millimeters
	int _wheelDistance; // distance between wheels in 
	double _xPosition, _yPosition, _theta; 
	double _degreesPerMillimeter;
	PositionControl *_leftWheel;
	PositionControl *_rightWheel;
};

#endif