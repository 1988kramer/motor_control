// DifferentialDrive
// by Andrew Kramer

// This class is completely untested!!!

#include"Arduino.h"
#include<PositionControl.h>
#include<DifferentialDrive.h>
#include<math.h>

const int straightRadius = 32767;

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
	_degreesPerMillimeter = 360.0 / (double)wheelCirc;
}

void DifferentialDrive::drive(int speed, int radius)
{
	int leftSpeed, rightSpeed;
	findSpeeds(speed, radius, leftSpeed, rightSpeed);

	_leftWheel->setSpeed(leftSpeed);
	_rightWheel->setSpeed(rightSpeed);
}

void DifferentialDrive::drive(int speed, int radius, int distance)
{
	int leftSpeed, rightSpeed;
	findSpeeds(speed, radius, leftSpeed, rightSpeed);

	// this definitely doesn't correctly control turning direction 
	double phi = (double)distance / (double)radius;
	int distanceDiff = phi * ((double)_wheelDistance / 2.0);
	int leftDistance = distance - distanceDiff;
	int rightDistance = distance + distanceDiff;

	int leftDegrees = leftDistance * _degreesPerMillimeter;
	int rightDegrees = rightDistance * _degreesPerMillimeter;

	_leftWheel->rotate(leftDegrees, leftSpeed);
	_rightWheel->rotate(rightDegrees, rightSpeed);
}

// finds speeds for bot to drive in a certain radius
// positive ragius will make the bot turn left
// negative radius will make the bot turn right
void DifferentialDrive::findSpeeds(int speed, int radius, 
									int &leftSpeed, int &rightSpeed)
{
	if (radius < straightRadius)
	{
		// calculate speed differential
		double botAngularVelocity = (double)speed / (double)radius;
		int speedDifferential = botAngularVelocity * ((double)_wheelDistance / 2.0);

		// calculate tangential speeds for left and right wheels;
		int leftTangential = speed - speedDifferential;
		int rightTangential = speed + speedDifferential;

		// calculate angular speeds for left and right wheels
		leftSpeed = leftTangential * _degreesPerMillimeter;
		rightSpeed = rightTangential * _degreesPerMillimeter;
	}
	else
	{
		leftSpeed = speed;
		rightSpeed = speed;
	}
}

void DifferentialDrive::getPosition(int &x, int &y, double &theta)
{
	x = _xPosition;
	y = _yPosition;
	theta = _theta;
}

void DifferentialDrive::update()
{
	_leftWheel->adjustPWM();
	_rightWheel->adjustPWM();
	updatePosition();
}

// still isn't working
void DifferentialDrive::updatePosition()
{
	double dLeft = _leftWheel->getDistance();
	double dRight = _rightWheel->getDistance();
	double dCenter = (dLeft + dRight) / 2;
	double phi = (dLeft + dRight) / (double)_wheelDistance;
	_theta += phi;
	_xPosition += dCenter * cos((double)_theta);
	_yPosition += dCenter * sin((double)_theta);
}

