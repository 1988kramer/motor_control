// Encoder
// by Andrew Kramer

// initializes an object to read input from a shaft encoder and
// track the number of encoder ticks using interrupts
// only works with Arduino Uno, Duemilanove, and others that
// have interrupt 0 defined as digital pin 2 and interrupt 1
// defined as digital pin 3

#include "Encoder.h"
#include "Arduino.h"

#define INTERRUPT0 = 2
#define INTERRUPT1 = 3

Encoder::Encoder(int encoderA, int encoderB, int count, 
				 int deltaT, int ticksPerRev)
{
	_encoderA = encoderA;
	_encoderB = encoderB;
	_count = count;
	_deltaT = deltaT;
	_degPerTick = 360.0 / (double)ticksPerRev;
	_oldCount = 0;
	_newCount = 0;
	_index = 0;
	pinMode(_encoderA, INPUT);
	pinMode(_encoderB, INPUT);
	if (_encoderA == INTERRUPT0) attachInterrupt(0, updateCount, CHANGE);
	if (_encoderA == INTERRUPT1) attachInterrupt(1, updateCount, CHANGE);
}

Encoder::getSpeed()
{
	// calculate number of ticks elapsed since in last deltaT
	double difference = abs(_count);
	_totalCount += count;
	resetCount();
	double ticksPerSec = difference / (_deltaT / 1000000);
	double degPerSec = ticksPerSec * _degPerTick;
	return (int)degPerSec;
}

Encoder::getDistance()
{
	int distance = _degPerTick * totalCount;
	_totalCount = 0;
	return distance;
}

Encoder::resetCount()
{
	_count = 0;
}

Encoder::updateCount()
{
	if (digitalRead(_encoderA == HIGH))
	{
		if (digitalRead(_encoderB == LOW))
			_count++;
		else
			_count--;
	}
	else
	{
		if (digitalRead(_encoderB == LOW))
			_count--;
		else
			_count++;
	}
}