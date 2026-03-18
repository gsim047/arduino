#include <Arduino.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>

// KY-028 датчик температуры

// D2 - 4
#define DPIN 4
// A0 - 17
#define APIN A0



void setup() 
{
	Serial.begin(115200);
	pinMode(DPIN, INPUT);
	pinMode(APIN, INPUT);
  
	Serial.println("\nStart!");
}// setup


void loop() 
{
	int dres = digitalRead(DPIN);
	float ares = analogRead(APIN);

//	ds.requestTemperatures(); // считывание значение температуры
	Serial.printf("%d %f\n", dres, ares);

	delay(1000);
}// loop
