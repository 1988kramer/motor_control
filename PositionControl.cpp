// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control

#include"Arduino.h"
#include<PositionControl.h>
//#include<Motor.h>
//#include<Encoder.h>

PositionControl::PositionControl(SpeedControl *speedControl)
{
	_speedControl = speedControl;
	_distance = 0;
}

void PositionControl::setSpeed(int speed)
{
	_speedControl->setSpeed(speed);
}

// rotates motor by the specified number of degrees at the 
// specified speed
// does not currently correct for overshoot
void PositionControl::rotate(int degrees, int speed)
{
	_distance += _speedControl->getDistance();
	if (degrees < 0)
		speed *= -1;
	int error = degrees;
	while (error > 0)
	{
		int tempDistance = _speedControl->getDistance();
		error -= tempDistance;
		_distance += tempDistance;
		double kP = (double)error / (double)degrees;
		int curSpeed = (double)speed * kP;
		(kP > 0.25) ? _speedControl->setSpeed(speed) : _speedControl->setSpeed(curSpeed);
		delay(100); // probably need better way to delay
	}
	_speedControl->setSpeed(0);
}

int PositionControl::getDistance()
{
	_distance += _speedControl->getDistance();
	int tempDistance = _distance;
	_distance = 0;
	return tempDistance;
}
