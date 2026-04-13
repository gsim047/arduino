#include <Arduino.h>
#include <gmFn.h>
//#include <gmUrl.h>

// датчик осввещённости

int dataPin = A0;
int oldval = 0;
int n = 0;


void setup()
{
	pinMode(dataPin, INPUT);
	Serial_init();

}// setup


void loop()
{
	n++;
	int val = analogRead(dataPin);
	int delta = val - oldval;
	if ( delta < 0 ) 
		delta = -delta;
	if ( delta > 25 ){
		Serial.printf("%d: %d\n", n, val);
		oldval = val;
	}
	delay(10);
}// loop

