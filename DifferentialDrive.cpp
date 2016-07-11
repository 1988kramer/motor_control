// DifferentialDrive
// by Andrew Kramer

#include"Arduino.h"
#include<PositionControl.h>
#include<DifferentialDrive.h>

DifferentialDrive::DifferentialDrive(PositionControl *lhWheel, 
								 PositionControl *rhWheel,
				 				 int wheelCirc, int wheelDistance)
{
	_leftWheel = lhWheel;
	_rightWheel = rhWheel;
	_wheelCirc = wheelCirc;
	_wheelDistance = wheelDistance;
	_degreesPerMillimeter = (double)wheelCirc / 360.0;
}

void DifferentialDrive::drive(int speed, int radius)
{
	// calculate speed differential
	double botAngularVelocity = (double)speed / (double)radius;
	int speedDifferential = botAngularVelocity * ((double)_wheelDistance / 2.0);

	// calculate tangential speeds for left and right wheels;
	int leftTangential = speed + speedDifferential;
	int rightTangential = speed - speedDifferential;

	// calculate angular speeds for left and right wheels
	int leftWheelAngular = leftTangential * _degreesPerMillimeter;
	int rightWheelAngular = rightTangential * _degreesPerMillimeter;

	_leftWheel->setSpeed(leftWheelAngular);
	_rightWheel->setSpeed(rightWheelAngular);
}

void DifferentialDrive::drive(int speed, int radius, int distance)
{

}

void DifferentialDrive::update()
{
	_leftWheel->adjustPWM();
	_rightWheel->adjustPWM();
	updatePosition();
}

void DifferentialDrive::updatePosition()
{

}

