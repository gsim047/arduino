#include <Arduino.h>
#include <gmBlink.h>

int n = 0;
ADC_MODE(ADC_VCC);

gmBlink b; //(14);
//int ledx = 14; //LED_BUILTIN; //0;
// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


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
	Serial.println(n);
	Serial.println(vcc);
}// loop
