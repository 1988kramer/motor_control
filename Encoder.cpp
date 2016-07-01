// Encoder
// by Andrew Kramer

// initializes an object to read input from a shaft encoder and
// track the number of encoder ticks using interrupts
// only works with Arduino Uno, Duemilanove, and others that
// have interrupt 0 defined as digital pin 2 and interrupt 1
// defined as digital pin 3

#include "Encoder.h"
#include "Arduino.h"

#define INTERRUPT0 2
#define INTERRUPT1 3

Encoder::Encoder(int encoderA, int encoderB, 
				 int deltaT, int ticksPerRev)
{
	_encoderA = encoderA;
	_encoderB = encoderB;
	_count = 0;
	_oldCount = 0;
	_newCount = 0;
	_totalCount = 0;
	_lastSpeed = 0;
	_deltaT = deltaT;
	_degPerTick = 360.0 / (double)ticksPerRev;
	pinMode(_encoderA, INPUT);
	pinMode(_encoderB, INPUT);
}

// calculates difference properly but does not return accurate speed
int Encoder::getSpeed()
{
	// calculate number of ticks elapsed since in last deltaT
	_oldCount = _newCount;
	_newCount = _count;
	double difference = _newCount - _oldCount;

	Serial.println((int)difference);

	_totalCount += (int)difference;
	double degPerSec;
	if (difference < 50000.0)
	{
		double ticksPerSec = difference / (_deltaT / 1000000);
		degPerSec = ticksPerSec * _degPerTick;
	}
	else
	{
		degPerSec = _lastSpeed;
	}
	_lastSpeed = degPerSec;
	return (int)degPerSec;
}

int Encoder::getDistance()
{
	int distance = _degPerTick * _totalCount;
	_totalCount = 0;
	return distance;
}

void Encoder::resetCount()
{
	_count = 0;
}

void Encoder::updateCount()
{
	if (digitalRead(_encoderA) == HIGH)
	{
		if (digitalRead(_encoderB) == LOW)
			_count++;
		else
			_count--;
	}
	else
	{
		if (digitalRead(_encoderB) == LOW)
			_count--;
		else
			_count++;
	}
}

