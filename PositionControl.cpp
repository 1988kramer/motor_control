// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control

#include"Arduino.h"
#include<PositionControl.h>
#include<SpeedControl.h>
//#include<Motor.h>
//#include<Encoder.h>

const double defaultKP = 2.0;

PositionControl::PositionControl(SpeedControl *speedControl)
{
	_speedControl = speedControl;
	_distance = 0;
	_kP = defaultKP;
	_positioning = false;
	_rotateDegrees = 0;
	_error = 0;
	_speed = 0;
}

void PositionControl::setKP(double kP) 
{
	_kP = kP;
}

void PositionControl::setSpeed(int speed)
{
	_speedControl->setSpeed(speed);
	_speed = speed;
}

// rotates motor by the specified number of degrees at the 
// specified speed
// motors cannot rotate simultaneously
// motors do not stop when rotating backward
void PositionControl::rotate(int degrees, int speed)
{
	if (!_positioning)
	{
		if (degrees < 0) 
		{
			speed *= -1;
			degrees *= -1;
		}
		_distance += _speedControl->getDistance();
		_error = degrees;
		_rotateDegrees = degrees;
		_speed = speed;
		_positioning = true;
	}
}

void PositionControl::adjustPWM()
{
	if (_positioning)
	{
		int thisDistance = _speedControl->getDistance();
		_distance += thisDistance;
		if (thisDistance < 0) thisDistance *= -1;
		_error -= thisDistance;

		int newSpeed = (double)_error * _kP;
		if (newSpeed < _speed)
		{
			_speed = newSpeed;
		}
		
		if (_error == 0 && thisDistance == 0)
		{
			_positioning = false;
			_speed = 0;
			_rotateDegrees = 0;
			_error = 0;
		}
		_speedControl->setSpeed(_speed);
	}
	_speedControl->adjustPWM();
}

// doesn't return correct distance
int PositionControl::getDistance()
{
	int tempDistance = _distance;
	_distance = 0;
	return tempDistance;
}
