#include <Arduino.h>
#include <gmFn.h>
//#include <gmUrl.h>

// датчик влажности YL-69 (FC-28)

int dataPin = A0;


void setup()
{
	pinMode(dataPin, INPUT);
	Serial_init();

}// setup


void loop()
{
	int sensorValue = analogRead(dataPin);
	Serial.println(sensorValue);
	delay(10000);
}// loop

