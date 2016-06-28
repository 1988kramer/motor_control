
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int dir1, int dir2, int pwm)
{
	_dir1 = dir1;
	_dir2 = dir2;
	_pwm = pwm;
	pinMode(_dir1, OUTPUT);
	pinMode(_dir2, OUTPUT);
	pinMode(_pwm, OUTPUT);
}

void Motor::setFwd()
{
	digitalWrite(_dir1, HIGH);
	digitalWrite(_dir2, LOW);
}

void Motor::setBack()
{
	digitalWrite(_dir1, LOW);
	digitalWrite(_dir2, HIGH);
}

void Motor::setFree()
{
	digitalWrite(_dir1, LOW);
	digitalWrite(_dir2, LOW);
}

void Motor::setStop()
{
	digitalWrite(_dir1, HIGH);
	digitalWrite(_dir2, HIGH);
}

void Motor::setPWM(int level)
{
	analogWrite(_pwm, level);
}