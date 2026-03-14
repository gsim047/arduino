#include <Arduino.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>

#define DPIN 4
// A0 - 17
#define APIN A0

int n = 0;
float last = 0.;


void setup() 
{
	Serial.begin(115200);
	pinMode(DPIN, INPUT);
	pinMode(APIN, INPUT);
  
	Serial.println("\nStart!");
	n = 1;
}// setup


void loop() 
{
	int dres = digitalRead(DPIN);
	float ares = analogRead(APIN);

	float dl = 0.;
	if ( ares > last )
		dl = ares - last;
	else
		dl = last - ares;

	if ( dl >= 5. ){
		Serial.printf("%d: %d %.0f\n", n, dres, ares);
	}

	n++;
	last = ares;
	delay(100);
}// loop
