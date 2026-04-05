#include <Arduino.h>

// геркон:
//  нога 1 - на GND
//  нога 2 - на D2
//  нога 2 - через резистор 10 кОм на 5В

const int pin = 4; // GPIO4 - это пин D2 на Wemos D1 Mini/NodeMCU
const int led = 2; // BUILDIN
static int state = LOW;


void setup() 
{
	Serial.begin(115200);
	// Используем встроенный резистор подтяжки к 3.3V
	pinMode(pin, INPUT_PULLUP);
	pinMode(led, HIGH);
}// setup


void loop() 
{
	int rdState = digitalRead(pin);

	if ( state != rdState ){
		if ( rdState == LOW ){
			Serial.println("closed (magnet is near)");
			digitalWrite(led, HIGH);
		}else{
			Serial.println("open (magnet is far)");
			digitalWrite(led, LOW);
		}
		state = rdState;
	}
	delay(50);
}// loop
