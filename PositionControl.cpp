// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control

#include"Arduino.h"
#include<PositionControl.h>
#include<SpeedControl.h>

const double defaultKP = 2.0;

PositionControl::PositionControl(SpeedControl *speedControl)
{
	_speedControl = speedControl;
	_distance = 0;
	_kP = defaultKP;
	_positioning = false;
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
void PositionControl::rotate(int degrees, int speed)
{
	if (!_positioning)
	{
		if (degrees < 0 && speed > 0) 
		{
			speed *= -1;
		}
		else if (speed < 0 && degrees > 0)
		{
			degrees *= -1;
		}
		else if (speed < 0 && degrees < 0)
		{
			degrees *= -1;
			speed *= -1;
		}
		_distance += _speedControl->getDistance();
		_error = degrees;
		_speed = speed;
		_positioning = true;
	}
}

void PositionControl::adjustPWM()
{
	int thisDistance = _speedControl->getDistance();
	_distance += thisDistance;
	if (_positioning)
	{
		_error -= thisDistance;

		int newSpeed = (double)_error * _kP;
		constrainSpeed(newSpeed);
		if (_error < 2 && _error > -2)
		{
			_positioning = false;
			_speed = 0;
			newSpeed = 0;
			_error = 0;
		}
		_speedControl->setSpeed(newSpeed);
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

void PositionControl::constrainSpeed(int &newSpeed)
{
	if (abs(_speed) < abs(newSpeed)) newSpeed = _speed;
}
