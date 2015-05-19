#include <Arduino.h>
#include <Wire.h>
#include "FooLib.h"

#include "FastLED.h"
#define NUM_LEDS 35
#define DATA_PIN 24
#define CLOCK_PIN 22
CRGB leds[NUM_LEDS];
void setup() { FastLED.addLeds<APA102,DATA_PIN,CLOCK_PIN>(leds, NUM_LEDS); int i=0; }
void loop() {
	int i =0;
	while (true){
		i = (i+1) % NUM_LEDS;
    leds[i] = CRGB::White; FastLED.show(); delay(30);
    leds[i] = CRGB::Black; FastLED.show(); delay(30);
	}
}

