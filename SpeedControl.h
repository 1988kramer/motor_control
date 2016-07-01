// SpeedControl
// by Andrew Kramer

// Provides speed control for a single DC motor
// uses PID control algorithm adapted from 
// Brett Beauregard's PID library for arduino

#ifndef SpeedControl_h
#define SpeedControl_h

#include"Arduino.h"
#include<Motor.h>
#include<Encoder.h>

class SpeedControl
{
public:
	SpeedControl(Motor *motor, Encoder *encoder);
	void setGains(double kP, double kI, double kD);
	void setSpeed(int speed); // in degrees/s
	void setMinSpeed(int minSpeed);
	int getDistance(); // returns total distance rotated in degrees
	void adjustPWM();
private:
	int _setPoint, _pwm, _minSpeed, _lastSpeed;
	double _iTerm, _kP, _kI, _kD;
	Motor *_motor;
	Encoder *_encoder;
	void constrainPWM();
};

#endif
