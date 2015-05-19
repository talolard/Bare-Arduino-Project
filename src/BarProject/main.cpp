#include "Strip.h"
Strip S;
void setup() {
  // Start up the LED strip

	Serial.begin(9600);

  // Update the strip, to start they are all 'off'

  randomSeed(analogRead(0));
}
void loop() {


Serial.println("Restart");

	int i=0;
  while (true){


	  S.Test();




  }
}

