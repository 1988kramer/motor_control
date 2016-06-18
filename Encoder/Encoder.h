// Encoder
// by Andrew Kramer

// initializes an object to read input from a shaft encoder and
// track the number of encoder ticks using interrupts
// only works with Arduino Uno, Duemilanove, and others that
// have interrupt 0 defined as digital pin 2 and interrupt 1
// defined as digital pin 3

#ifndef Encoder_h
#define Encoder_h

#include "Arduino.h"

class Encoder
{
public:
	Encoder(int encoderA, int encoderB, int &count, int deltaT);
	void resetCount();
	int getSpeed(); // returns speed in ticks per second
	long getTotalCount(); // returns total count and resets totalCount to 0
private:
	int _encoderA, _encoderB; // encoder pins
	volatile long _count;
	int _deltaT; // in microseconds
	long _totalCount;
	void updateCount();
};

#endif