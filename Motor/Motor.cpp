
#include "Arduino.h"
#include "Motor.h"

Motor::Motor(int dir1, int dir2, int pwm)
{
	_dir1 = dir1;
	_dir2 = dir2;
	_pwm = pwm;
	pinMode(dir1, OUTPUT);
	pinMode(dir2, OUTPUT);
	pinMode(pwm, OUTPUT);
}

Motor::setFwd()
{
	digitalWrite(_dir1, HIGH);
	digitalWrite(_dir2, LOW);
}

Motor::setBack()
{
	digitalWrite(_dir1, LOW);
	digitalWrite(_dir2, HIGH);
}

Motor::setFree()
{
	digitalWrite(_dir1, LOW);
	digitalWrite(_dir2, LOW);
}

Motor::setStop()
{
	digitalWrite(_dir1, HIGH);
	digitalWrite(_dir2, HIGH);
}

Motor::setPWM(int level)
{
	analogWrite(_pwm, level);
}