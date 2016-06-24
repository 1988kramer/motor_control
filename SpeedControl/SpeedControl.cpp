// SpeedControl
// by Andrew Kramer

// Provides speed control for a single DC motor
// uses PID control algorithm adapted from 
// Brett Beauregard's PID library for arduino

#include"Arduino.h"
#include"SpeedControl.h"
#include<TimerOne.h>
#include<Motor.h>
#include<Encoder.h>

#define DEFAULT_MIN_SPEED 10

SpeedControl::SpeedControl(Motor motor, Encoder encoder)
{
	_encoder = encoder;
	_motor = motor;
	_iTerm = 0;
	_pwm = 0;

	_kP = 1;
	_kI = 1;
	_kD = 1;

	_setPoint = 0;
	_minSpeed = DEFAULT_MIN_SPEED;
	
	// timer must be initialized outside of this class
	// when motor object is created
	// use same deltaT for both
	TimerOne.attachInterupt(adjustPWM);
}

SpeedControl::SetGains(int kP, int kI, int kD)
{
	_kP = kP;
	_kI = kI;
	_kD = kD;
}

SpeedControl::setMinSpeed(int minSpeed)
{
	_minSpeed = minSpeed;
}

SpeedControl::setSpeed(int speed)
{
	if (speed < 0)
	{
		motor.setBack();
		speed *= -1;
	}
	else
	{
		motor.setFwd();
	}
	if (speed < _minSpeed && speed > 0)
		_setPoint = _minSpeed;
	else
		_setPoint = speed;
}

SpeedControl::getDistance()
{
	encoder.getDistance();
}

SpeedControl::adjustPWM()
{
	int speed = _encoder.getSpeed();
	double error = _setPoint - speed;
	_iTerm += (_kI * error);
	double dInput = speed - _lastSpeed;
	int adjustment = (_kP * error) + _iTerm + (_kD * dInput);
	_pwm += adjustment;
	constrainPWM();
	motor.setPWM(_pwm);
	_lastSpeed = speed;
}

SpeedControl::constrainPWM()
{
	if (_pwm > 255) _pwm = 255;
	else if (_pwm < 0) _pwm = 0;
}
