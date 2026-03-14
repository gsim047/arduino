#include <Arduino.h>

#define DPIN 4

int n = 0;


void setup() 
{
	Serial.begin(115200);
	pinMode(DPIN, OUTPUT);
	digitalWrite(DPIN, LOW);
  
    n = 0;
	Serial.println("\nStart!");
}// setup


void loop() 
{
	digitalWrite(DPIN, HIGH);
	delay(4000);
	digitalWrite(DPIN, LOW);

	n++;
	Serial.printf("%d\n", n);

	delay(4000);
}
