#include <Arduino.h>
#include <gmBlink.h>

int n = 0;
ADC_MODE(ADC_VCC);

gmBlink b(0); //(14);


void setup() 
{
	Serial.begin(115200);
	//pinMode(ledx, OUTPUT);
	n = 0;
}// setup


void loop() 
{
	b.blink(100);
	delay(500);
	n++;
	int vcc = ESP.getVcc();
	Serial.printf("%d: %d\n", n, vcc);
}// loop
