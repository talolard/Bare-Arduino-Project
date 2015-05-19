/*#include <Arduino.h>
#include <Wire.h>
#include "BarLib.h"

#include "SPI.h"
#include "globals.h"


uint32_t genRandomColor()
{
  int a,b,c;

   a = random(255);
    b = random(255-a);
    c = random(255-a-b);
    int perm = random(6);
    switch (perm){
      case 0:{
        return strip.Color(a,b,c);
      break;}
      case 1:{
        return strip.Color(a,c,b);
      break;}
      case 2:{
        return strip.Color(b,a,c);
      break;}
      case 3:{
        return strip.Color(b,c,a);
      break;}
      case 4:{
        return strip.Color(c,a,b);
      break;}
      case 5:{
        return strip.Color(c,b,a);
      break;}
    }

}

// Chase one dot down the full strip.  Good for testing purposes.

void makeTail(uint32_t start,uint32_t space, uint32_t c)
{
   for (int i =1; i< space; i++){
       strip.setPixelColor(start+i, 0); // Set new pixel 'on'
       strip.setPixelColor(start-i, 0); // Set new pixel 'on'

   }
   strip.setPixelColor(start, c); // Set new pixel 'on'
}
void setPixel(uint32_t i, uint32_t c,uint8_t tailSize)
{
    Serial.print(i);
    Serial.print("\n");
    strip.setPixelColor(i, c); // Set new pixel 'on'
    strip.setPixelColor(i-tailSize, 0); // Set new pixel 'on'
    strip.setPixelColor(i+tailSize, 0); // Set new pixel 'on'
    strip.show();              // Refresh LED states


}
void colorChase(uint32_t c, uint8_t wait,uint8_t tailSize) {
  int i;
  int numPixels=35;


  // Start by turning all pixels off:


  // Then display one pixel at a time:
  c =genRandomColor();
  for(i=0; i<numPixels; i++) {
    int randNum = random(1000);
    if (randNum>wait/10){
      wait = wait*0.995;
    }
    else{
      wait = wait *1.005;
    }
    for(int r=0;r<255;r++){
    	setPixel(i+2,c,tailSize);
    	for(int g=0;r<255;r++){
    		setPixel(i+1,c,tailSize);
    		for(int b=0;r<255;r++){
    			c = strip.Color(r,g,b);


    			setPixel(i,c,tailSize);
    			delay(30);
    		}
    	}
    }
    delay(wait);


  }




  strip.show(); // Refresh to turn off last pixel
}

*/
