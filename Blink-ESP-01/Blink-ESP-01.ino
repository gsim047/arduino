#include <Arduino.h>
#include <gmBlink.h>


gmBlink b("BUILTIN");


void setup() 
{
//  pinMode(4, OUTPUT);
	Serial.begin(115200);
}// setup


void loop() 
{
	b.bl(50);
	delay(500);
//  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(1000);                       // wait for a second
//  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
//  delay(1000);                       // wait for a second

	int sensorValue = analogRead(A0);
  // Convert the analog reading (which goes from 0 - 1023) to a voltage (0 - 5V):
	float voltage = sensorValue * (5.0 / 1023.0);
  // print out the value you read:
	Serial.println(voltage);
}// loop
