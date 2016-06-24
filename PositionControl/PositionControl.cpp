// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control

#include"Arduino.h"
#include<PositionControl.h>
#include<Motor.h>
#include<Encoder.h>

PositionControl::PositionControl(SpeedControl speedControl)
{
	_speedControl = speedControl;
	_distance = 0;
}

PositionControl::setSpeed(int speed)
{
	_speedControl.setSpeed(speed);
}

PositionControl::rotate(int degrees, int speed)
{
	_distance += _speedControl.getDistance();
	if (degrees < 0)
		speed *= -1;
	int error = degrees;
	while (error > 0)
	{
		error -= _speedControl.getDistance();
		int curSpeed = (double)speed * ((double)error / (double)degrees);
		_speedControl.setSpeed(curSpeed);
		delay(100); // probably need better way to delay
	}
}

PositionControl::getDistance()
{
	_distance += _speedControl.getDistance();
	int tempDistance = _distance;
	_distance = 0;
	return tempDistance;
}