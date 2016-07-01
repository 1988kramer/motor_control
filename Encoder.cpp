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
	_totalCount = 0;
	_deltaT = deltaT;
	_degPerTick = 360.0 / (double)ticksPerRev;
	pinMode(_encoderA, INPUT);
	pinMode(_encoderB, INPUT);
}

// getSpeed does not work, it's not even being called
int Encoder::getSpeed()
{
	// calculate number of ticks elapsed since in last deltaT
	double difference = (double)_count;
	Serial.print("reset");
	Serial.print("\n");
	_totalCount += _count;
	resetCount();
	double ticksPerSec = difference / (_deltaT / 1000000);
	double degPerSec = ticksPerSec * _degPerTick;
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
	Serial.print(_count);
	Serial.print("\n");
}

