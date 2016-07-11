// DifferentialDrive
// by Andrew Kramer

// This class is completely untested!!!

#include"Arduino.h"
#include<PositionControl.h>
#include<DifferentialDrive.h>
#include<math.h>

DifferentialDrive::DifferentialDrive(PositionControl *lhWheel, 
								 PositionControl *rhWheel,
				 				 int wheelCirc, int wheelDistance)
{
	_leftWheel = lhWheel;
	_rightWheel = rhWheel;
	_wheelCirc = wheelCirc;
	_wheelDistance = wheelDistance;
	_xPosition = 0;
	_yPosition = 0;
	_theta = 0;	
	_degreesPerMillimeter = (double)wheelCirc / 360.0;
}

void DifferentialDrive::drive(int speed, int radius)
{
	int leftSpeed, rightSpeed;
	findSpeeds(speed, radius, &leftSpeed, &rightSpeed);

	_leftWheel->setSpeed(leftSpeed);
	_rightWheel->setSpeed(rightSpeed);
}

void DifferentialDrive::drive(int speed, int radius, int distance)
{
	int leftSpeed, rightSpeed;
	findSpeeds(speed, radius, &leftSpeed, &rightSpeed);

	// this definitely doesn't correctly control turning direction 
	double phi = (double)distance / (double)radius;
	int dRight = phi * ((double)radius - ((double)_wheelDistance / 2.0));
	int dLeft = phi * ((double)radius + ((double)_wheelDistance / 2.0));

	_leftWheel->rotate(leftSpeed, dLeft);
	_rightWheel->rotate(rightSpeed, dRight);
}

// finds speeds for bot to drive in a certain radius
// not sure if it will accurately control direction
// and I haven't defined the coordinate system
void DifferentialDrive::findSpeeds(int speed, int radius, 
									int &leftSpeed, int &rightSpeed)
{
	// calculate speed differential
	double botAngularVelocity = (double)speed / (double)radius;
	int speedDifferential = botAngularVelocity * ((double)_wheelDistance / 2.0);

	// calculate tangential speeds for left and right wheels;
	int leftTangential = speed + speedDifferential;
	int rightTangential = speed - speedDifferential;

	// calculate angular speeds for left and right wheels
	int leftSpeed = leftTangential * _degreesPerMillimeter;
	int rightSpeed = rightTangential * _degreesPerMillimeter;
}

void DifferentialDrive::update()
{
	_leftWheel->adjustPWM();
	_rightWheel->adjustPWM();
	updatePosition();
}

void DifferentialDrive::updatePosition()
{
	double dLeft = _leftWheel->getDistance();
	double dRight = _rightWheel->getDistance();
	double dCenter = (dLeft + dRight) / 2;
	double phi = (dLeft + dRight) / (double)_wheelDistance;
	_theta += phi;
	_xPosition += dCenter * math.cos(_theta);
	_yPosition += dCenter * math.sin(_theta);
}

