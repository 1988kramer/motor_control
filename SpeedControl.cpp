// SpeedControl
// by Andrew Kramer

// Provides speed control for a single DC motor
// uses PID control algorithm adapted from 
// Brett Beauregard's PID library for arduino

#include"Arduino.h"
#include"SpeedControl.h"
#include<Motor.h>
#include<Encoder.h>

#define DEFAULT_MIN_SPEED 60
const double defaultGain = 1.0;

// accepts a pointer to a Motor and a pointer to an Encoder as parameters
// sets gains to 1.0 and minimum speed to 60 by default
SpeedControl::SpeedControl(Motor *motor, Encoder *encoder)
{
	_encoder = encoder;
	_motor = motor;
	_iTerm = 0;
	_pwm = 0;
	_lastSpeed = 0;

	_kP = defaultGain;
	_kI = defaultGain;
	_kD = defaultGain;

	_setPoint = 0; // in degrees/second
	_minSpeed = DEFAULT_MIN_SPEED;
}

// accepts three doubles as parameters
//   kP - the proportional gain
//   kI - the integral gain
//   kD - the derivative gain
// sets the PID gains to the given values
void SpeedControl::setGains(double kP, double kI, double kD)
{
	_kP = kP;
	_kI = kI;
	_kD = kD;
}

// accepts an int as a parameter
// sets the min speed to the given value
void SpeedControl::setMinSpeed(int minSpeed)
{
	_minSpeed = minSpeed;
}

// accepts an int, speed in degrees/second, as a parameter
// changes the set point to the abs(speed) if abs(speed) is
// above the min speed
// changes the set point to the min speed if abs(speed) is
// between min speed and 0
// sets motor direction to backward if speed is negative
// sets motor direction to freewheel if speed is 0
void SpeedControl::setSpeed(int speed)
{
	if (speed < 0)
	{
		_motor->setBack();
		speed *= -1;
	}
	else if (speed > 0)
	{
		_motor->setFwd();
	}
	if (speed == 0)
	{
		_motor->setFree();
	}
	if (speed < _minSpeed && speed > 0)
		speed = _minSpeed;
	_setPoint = speed;
}

// returns the distance rotated by the motor's output shaft in degrees
// since the last call to getDistance()
int SpeedControl::getDistance()
{
	return _encoder->getDistance();
}

// adjusts motor's PWM level to correct for any error between the
// set point and the actual speed of the motor's output shaft
// MUST be called regularly on the same deltaT used to calculate
// motor speed in the Encoder object
void SpeedControl::adjustPWM()
{
	int speed = _encoder->getSpeed(); // motor control returns vector speed
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
