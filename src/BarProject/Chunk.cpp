/*
 * Chunk.cpp
 *
 *  Created on: May 16, 2015
 *      Author: tal
 */

#include "Chunk.h"
#include "Strip.h"

RgbColor HsvToRgb(HsvColor hsv)
{
    RgbColor rgb;
    unsigned char region, remainder, p, q, t;

    if (hsv.s == 0)
    {
        rgb.r = hsv.v;
        rgb.g = hsv.v;
        rgb.b = hsv.v;
        return rgb;
    }

    region = hsv.h / 43;
    remainder = (hsv.h - (region * 43)) * 6;

    p = (hsv.v * (255 - hsv.s)) >> 8;
    q = (hsv.v * (255 - ((hsv.s * remainder) >> 8))) >> 8;
    t = (hsv.v * (255 - ((hsv.s * (255 - remainder)) >> 8))) >> 8;

    switch (region)
    {
        case 0:
            rgb.r = hsv.v; rgb.g = t; rgb.b = p;
            break;
        case 1:
            rgb.r = q; rgb.g = hsv.v; rgb.b = p;
            break;
        case 2:
            rgb.r = p; rgb.g = hsv.v; rgb.b = t;
            break;
        case 3:
            rgb.r = p; rgb.g = q; rgb.b = hsv.v;
            break;
        case 4:
            rgb.r = t; rgb.g = p; rgb.b = hsv.v;
            break;
        default:
            rgb.r = hsv.v; rgb.g = p; rgb.b = q;
            break;
    }

    return rgb;
}

HsvColor RgbToHsv(RgbColor rgb)
{
    HsvColor hsv;
    unsigned char rgbMin, rgbMax;

    rgbMin = rgb.r < rgb.g ? (rgb.r < rgb.b ? rgb.r : rgb.b) : (rgb.g < rgb.b ? rgb.g : rgb.b);
    rgbMax = rgb.r > rgb.g ? (rgb.r > rgb.b ? rgb.r : rgb.b) : (rgb.g > rgb.b ? rgb.g : rgb.b);

    hsv.v = rgbMax;
    if (hsv.v == 0)
    {
        hsv.h = 0;
        hsv.s = 0;
        return hsv;
    }

    hsv.s = 255 * long(rgbMax - rgbMin) / hsv.v;
    if (hsv.s == 0)
    {
        hsv.h = 0;
        return hsv;
    }

    if (rgbMax == rgb.r)
        hsv.h = 0 + 43 * (rgb.g - rgb.b) / (rgbMax - rgbMin);
    else if (rgbMax == rgb.g)
        hsv.h = 85 + 43 * (rgb.b - rgb.r) / (rgbMax - rgbMin);
    else
        hsv.h = 171 + 43 * (rgb.r - rgb.g) / (rgbMax - rgbMin);

    return hsv;
}
void Chunk::makeNextColor()
{
	hsv.h+=5;
	hsv.v+=5;
	hsv.s+=5;
	rgb =HsvToRgb(hsv);
}
Chunk::Chunk(Strip* s) {
	// TODO Auto-generated constructor stub

	Owner=s;
	hsv.h=0;
	hsv.s=0;
	hsv.v=0;

	init(random(3),random(3));

}

Chunk::~Chunk() {
	// TODO Auto-generated destructor stub
}
void Chunk::standStill(){
	r--;
	g--;
	b--;
	makeNextColor();
	for (int i = startPin; i<=endPin; i++){
			Owner->setLight(i,rgb.r,rgb.g,rgb.b);
	}
}
void Chunk::makeStep(){
	int direction;
	if (goesForward){
		direction =1;
	}
	else direction =-1;


	Serial.print(color);
		for (int i = startPin; i<=endPin; i++){
			Owner->setLight(i-direction,r,g,b);



		}

	if (goesForward){
		moveForward();
	}else{
		moveBack();
	}

}
void Chunk::nextStep()
{
	long  int randNum =millis();
	//if (randNum%11==0)
	{
		makeNextColor();
	}
	if ( standStillLeft<=0){
		makeStep();
		if (randNum %271==0){
			standStillLeft =millis() %15; // Standstill for 50 calls
		}
		if (randNum%51==0){
				reverse();
				ChangeColorRandom();
			}
		if (randNum%27==0){
			ShrinkBack();
			shrinkFront();
		}
	}


	else{//If we are standing still
		if (randNum%7==0){
			//growFront();
		}

		ShrinkBack();

		shrinkFront();
		if (Size()==0){
			Owner->waitTime=10;
		}
		standStill();

	}



}
void Chunk::ChangeColorRandom()
{
	color = Owner->makeColor(1,1,1);
	r = random(127);
	g = random(127);
	b = random(127);
	for (int i=startPin; i<endPin;i++ ){
			Owner->setLight(i,r,g,b);
	}

}
void Chunk::init (int start,int size)
{
	startPin = start;
	endPin = start+size;
	makeNextColor();
	goesForward = millis() %2;
	standStillLeft=0;
}
