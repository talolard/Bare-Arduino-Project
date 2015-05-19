/*
 * Strip.cpp
 *
 *  Created on: May 16, 2015
 *      Author: tal
 */

#include "Strip.h"
#include "Chunk.h"

Strip::Strip(){
	Serial.begin(9600);
	count=0;
	waitTime =100;
	waitLimit =200;

	strip = new LPD8806(nLEDS, DATAPIN, CLOCKPIN);

	strip->begin();
	clear();
	show();
	for (int i=0;i<NUMCHUNKS;i++){
		Serial.print(i);
		chunks[i] = new Chunk(this);

	}
	resetChunks();


}
Strip::~Strip() {
	for (int i=0;i<NUMCHUNKS;i++){
		delete chunks[i];
	}
	delete strip;

}
int Strip::modPin(int pin){
	while (pin <0){
			pin += nLEDS;
		}
		pin = pin%nLEDS;
		return pin;
}
void Strip::setLight(int pin,int r,int g,int b){

	pin = modPin(pin);
	if (lights[pin] !=0){
		r=r*2;
		g=g*2;
		b=b*2;

	}
	lights[pin]=1;
	strip->setPixelColor(pin, r,g,b); // Set new pixel 'on'
}
void Strip::setLight(int pin,int color){
	pin = modPin(pin);
	if (color==0){
		lights[pin] = color;
		strip->setPixelColor(pin, color); // Set new pixel 'on'
	}else{
		lights[pin] += color;
		int r =random(20);
		int g =random(20);
		int b =random(20);
		strip->setPixelColor(pin, r,g,b); // Set new pixel 'on'
	}

}
void Strip::clear(){
	int zero =0;
	for (int i=0; i< nLEDS;i++){
		setLight(i,zero);

	}
}

void Strip::show(){
	strip->show();
}
void Strip::Test(){
	clear();
	count++;
	if (count %100 ==0){
		waitTime = random(150);
		if (waitTime==99){
			blink();
		}
		if (waitTime>95 && waitTime<98){
			wobble();
			blinkModeCounter =100;
		}
	}
	if (count %150 ==0){
		resetChunks();
	}
	int randNum = random(1000);
	float something = millis()/1000.0;
	int value = waitTime * (1+ sin( something * 2.0 * PI  ));
	for (int i =0; i <NUMCHUNKS;i++){
		Serial.println(i);
		int randNum = random(1000);

		if (chunks[i]->Size()>0)
		chunks[i]->nextStep();


	}
	show();
	delay(value);
	if (value %3 ==0 && blinkModeCounter>0){
		blinkModeCounter--;
		clear();
		show();
		delay(value*5);
	}


}

void Strip::resetChunks(){
	int size = 1+millis()% 7;
	if (size <2 ){
		size =0;
		waitTime=100;
	}
	int lastEnd =0;
	int remaining = nLEDS-size-1;
	for (int i=0;i<(NUMCHUNKS);i++){
		chunks[i]->init(lastEnd+1  %remaining,size);
		lastEnd =chunks[i]->endPin;
		remaining = remaining -size;
		size = remaining;
	}
}
void Strip::PrintLights(){
	for (int i=0; i<nLEDS;i++){


		Serial.print(lights[i]);
		Serial.print(" ");
	}
	Serial.println("aaa");
}

void Strip::blink()
{
	clear();
	float something = millis()/1000.0;
	int color = random(255*255);
	int times =30;
	for (int value=30; value>0;value--){

			delay(value);

			for (int i=0; i<nLEDS;i++){
				setLight(i,color);
			}
			show();
			delay(value);

	}

}
void Strip::wobble()
{	Chunk& chunk = *chunks[0];
	chunk.init(16,3);
	int count=10;
	for (int time =0; time<5; time++){
			while(chunk.Size() >0){
				count++;
				chunk.shrinkFront();
				chunk.ShrinkBack();
				chunk.standStill();
				show();
				delay(random(10));
				clear();
				show();
				delay(random(count)+50);
			}
			while(chunk.Size() <nLEDS){
				chunk.growBack();
				chunk.growFront();
				chunk.standStill();
				show();
				delay(random(60));
				clear();
				show();
				delay(random(count)+50);
			}
	}
}
