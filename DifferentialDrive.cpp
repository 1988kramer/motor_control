// DifferentialDrive
// by Andrew Kramer

// This class is completely untested!!!

#include"Arduino.h"
#include<PositionControl.h>
#include<DifferentialDrive.h>
#include<math.h>

const double pi = 3.141592;

DifferentialDrive::DifferentialDrive(PositionControl *lhWheel, 
								 PositionControl *rhWheel,
				 				 int wheelCirc, int wheelDistance)
{
	_leftWheel = lhWheel;
	_rightWheel = rhWheel;
	_wheelCirc = wheelCirc;
	_wheelDistance = wheelDistance;
	_xPosition = 0.0;
	_yPosition = 0.0;
	_theta = 0.0;	
	_degreesPerMillimeter = 360.0 / (double)wheelCirc;
}

void DifferentialDrive::drive(int translational, double angular)
{
	int leftSpeed, rightSpeed;
	findSpeeds(translational, angular, leftSpeed, rightSpeed);

	_leftWheel->setSpeed(leftSpeed);
	_rightWheel->setSpeed(rightSpeed);
}

void DifferentialDrive::drive(int translational, double angular, int distance)
{
	int leftSpeed, rightSpeed;
	findSpeeds(translational, angular, leftSpeed, rightSpeed);

	double radius = (double)translational / angular;
	double phi = (double)distance / (double)radius;
	int distanceDiff = phi * ((double)_wheelDistance / 2.0);
	int leftDistance = distance - distanceDiff;
	int rightDistance = distance + distanceDiff;

	int leftDegrees = leftDistance * _degreesPerMillimeter;
	int rightDegrees = rightDistance * _degreesPerMillimeter;

	_leftWheel->rotate(leftDegrees, leftSpeed);
	_rightWheel->rotate(rightDegrees, rightSpeed);
}

// finds wheel speed required to give the bot a specified angular and
// translational velocity
// positive angular will make the bot turn left
// negative angular will make the bot turn right
void DifferentialDrive::findSpeeds(int translational, double angular, 
									int &leftSpeed, int &rightSpeed)
{
	// calculate speed differential
	int speedDifferential = angular * ((double)_wheelDistance / 2.0);

	// calculate tangential speeds for left and right wheels;
	int leftTangential = translational - speedDifferential;
	int rightTangential = translational + speedDifferential;

	// calculate angular speeds for left and right wheels
	leftSpeed = (double)leftTangential * _degreesPerMillimeter;
	rightSpeed = (double)rightTangential * _degreesPerMillimeter;
}

void DifferentialDrive::getPosition(double &x, double &y, double &theta)
{
	x = _xPosition;
	y = _yPosition;
	theta = _theta;
}

void DifferentialDrive::update()
{
	sei();
	_leftWheel->adjustPWM();
	_rightWheel->adjustPWM();
	updatePosition();
}

// seems to be working but not thoroughly tested
void DifferentialDrive::updatePosition()
{
	double leftDegrees = _leftWheel->getDistance();
	double rightDegrees = _rightWheel->getDistance();
	double dLeft = leftDegrees / _degreesPerMillimeter;
	double dRight = rightDegrees / _degreesPerMillimeter;
	double dCenter = (dLeft + dRight) / 2.0;
	double phi = (dRight - dLeft) / (double)_wheelDistance;
	_theta += phi;
	if (_theta > 2.0 * pi) _theta -= 2.0 * pi;
	if (_theta < 0.0) _theta += 2.0 * pi;
	_xPosition += dCenter * cos(_theta);
	_yPosition += dCenter * sin(_theta);
}

void DifferentialDrive::resetPosition()
{
	_xPosition = 0;
	_yPosition = 0;
	_theta = 0.0;
}

