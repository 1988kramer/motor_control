// Motor
// by Andrew Kramer

// controls direction and pwm input to a DC motor

#ifndef Motor_h
#define Motor_h

#include "Arduino.h"

class Motor
{
public:
	Motor(int dir1, int dir2, int pwm);
	void setFwd();
	void setBack();
	void setFree();
	void setStop();
	void setPWM(int level);
private:
	int _dir1, _dir2, _pwm;
};

#endif