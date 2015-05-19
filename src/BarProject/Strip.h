/*
 * Strip.h
 *
 *  Created on: May 16, 2015
 *      Author: tal
 */


#ifndef STRIP_H_
#define STRIP_H_
#define DATAPIN  24
#define CLOCKPIN  22
#define nLEDS 35
#define NUMCHUNKS 3
#include <Arduino.h>
#include <Wire.h>
#include "SPI.h"
#include "LPD8806.h"
class Chunk;
class Strip {


	int lights[nLEDS];
	Chunk* chunks[NUMCHUNKS];
	LPD8806* strip;
	int count;
	int modPin(int pin);
	void show();
public:
	void clear();
	int waitTime;
	int waitLimit;
	int blinkModeCounter;
	uint32_t makeColor(int r,int g,int b){return (255);}
	uint32_t getPinColor(int pin){pin = modPin(pin); return  lights[pin];}
	void resetChunks();
	void setLight(int pin,int color);
	void setLight(int pin,int r, int g, int b);
	void turnOff(int pin) {setLight(pin,0);}
	void blink();
	void wobble();
	void PrintLights();
	void Test();
	Strip() ;
	virtual ~Strip();
};

#endif /* STRIP_H_ */
