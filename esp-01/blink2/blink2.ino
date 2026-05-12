#include <Arduino.h>
#include <gmBlink.h>

int n = 0;
ADC_MODE(ADC_VCC);

gmBlink b(2);


void setup() 
{
	Serial.begin(115200);
	//pinMode(ledx, OUTPUT);
	n = 0;
	b.up();
}// setup


void loop() 
{
	//b.blink(100);
	delay(500);
	n++;
	if ( n % 3 == 0 ){
		b.down();
	}else{
		b.up();
	}
	int vcc = ESP.getVcc();
	Serial.printf("%d: %d\n", n, vcc);
}// loop
