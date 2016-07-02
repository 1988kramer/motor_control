// SpeedControl
// by Andrew Kramer

// Provides speed control for a single DC motor
// uses PID control algorithm adapted from 
// Brett Beauregard's PID library for arduino

#include"Arduino.h"
#include"SpeedControl.h"
#include<Motor.h>
#include<Encoder.h>

#define DEFAULT_MIN_SPEED 10

SpeedControl::SpeedControl(Motor *motor, Encoder *encoder)
{
	_encoder = encoder;
	_motor = motor;
	_iTerm = 0;
	_pwm = 0;
	_lastSpeed = 0;

	_kP = 1.0;
	_kI = 1.0;
	_kD = 1.0;

	_setPoint = 0;
	_minSpeed = DEFAULT_MIN_SPEED;
}

void SpeedControl::setGains(double kP, double kI, double kD)
{
	_kP = kP;
	_kI = kI;
	_kD = kD;
}

void SpeedControl::setMinSpeed(int minSpeed)
{
	_minSpeed = minSpeed;
}

void SpeedControl::setSpeed(int speed)
{
	if (speed < 0)
	{
		_motor->setBack();
		speed *= -1;
	}
	else
	{
		_motor->setFwd();
	}
	if (speed < _minSpeed)
		_setPoint = _minSpeed;
	else
		_setPoint = speed;
}

int SpeedControl::getDistance()
{
	return _encoder->getDistance();
}

void SpeedControl::adjustPWM()
{
	int speed = _encoder->getSpeed(); // motor control returns vector speed
	Serial.println(speed);
	if (speed < 0) speed *= -1;  // convert speed to scalar
	int error = _setPoint - speed;
	_iTerm += (_kI * (double)error);
	double dInput = speed - _lastSpeed;
	int adjustment = (_kP * (double)error) + _iTerm - (_kD * dInput);
	_pwm += adjustment;
	constrainPWM();
	_motor->setPWM(_pwm);
	_lastSpeed = speed;
}

void SpeedControl::constrainPWM()
{
	if (_pwm > 255) _pwm = 255;
	else if (_pwm < 0) _pwm = 0;
}
