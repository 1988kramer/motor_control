// PositionControl
// by Andrew Kramer

// Provides position control for a single DC motor
// via the PID control loop in Speed Control

#include"Arduino.h"
#include<PositionControl.h>
//#include<Motor.h>
//#include<Encoder.h>

const double defaultKP = 0.5;

PositionControl::PositionControl(SpeedControl *speedControl)
{
	_speedControl = speedControl;
	_distance = 0;
	_kP = defaultKP;
}

void PositionControl::setKP(double kP) 
{
	_kP = kP;
}

void PositionControl::setSpeed(int speed)
{
	_speedControl->setSpeed(speed);
}

// rotates motor by the specified number of degrees at the 
// specified speed
// motors cannot rotate simultaneously
// motors do not stop when rotating backward
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
		int adjustment = (double)error * _kP;
		if (error < speed && adjustment < speed) 
			speed -= adjustment;
		_speedControl->setSpeed(speed);
		delay(50); // probably need better way to delay
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
