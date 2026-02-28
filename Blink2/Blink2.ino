/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

int n = 0;
int delay1 = 100;
int delay2 = 1000;
ADC_MODE(ADC_VCC);

int levHIGH = HIGH;
int levLOW = LOW;

int ledx = 2;
int inv = 1;
// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(115200);
  pinMode(ledx, OUTPUT);

  n = 0;

  if ( inv ){
    levHIGH = LOW;
    levLOW = HIGH;
  }
}


void bl(int ledN, int lev1, int lev2, int del)
{
	digitalWrite(ledN, lev1);
	delay(del);
	digitalWrite(ledN, lev2);
}//


// the loop function runs over and over again forever
void loop() {
  
	bl(ledx, levHIGH, levLOW, delay1);
//  digitalWrite(ledx, levHIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(delay1);                       // wait for a second
//  digitalWrite(ledx, levLOW);    // turn the LED off by making the voltage LOW
	delay(delay1);                       // wait for a second
	bl(ledx, levHIGH, levLOW, delay1);
//  digitalWrite(ledx, levHIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(delay1);                       // wait for a second
//  digitalWrite(ledx, levLOW);    // turn the LED off by making the voltage LOW
	delay(delay2);                       // wait for a second
	n++;
  int vcc = ESP.getVcc();
  Serial.print(n);
  Serial.print(": ");
  Serial.println(vcc);
}
