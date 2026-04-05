#include <Arduino.h>

//#define DPIN 4
int pin = 4;   // D2
int led = 2;   // BUILTIN 

int n = 0;


void setup() 
{
	Serial.begin(115200);
	pinMode(led, OUTPUT);
	digitalWrite(pin, HIGH);
	pinMode(pin, OUTPUT);
	digitalWrite(pin, LOW);
  
    n = 0;
	Serial.println("\nStart!");
}// setup


void loop() 
{
	digitalWrite(pin, HIGH);
	digitalWrite(led, LOW);
	delay(4000);
	digitalWrite(pin, LOW);
	digitalWrite(led, HIGH);

	n++;
	Serial.println(n);

	delay(4000);
}// loop
