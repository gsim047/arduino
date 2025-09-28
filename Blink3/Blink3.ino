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
ADC_MODE(ADC_VCC);
int ledx = 0;

// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  Serial.begin(9600);
  pinMode(ledx, OUTPUT);
  n = 0;
}

// the loop function runs over and over again forever
void loop() {
  int lev1 = HIGH;
  int lev2 = LOW;
  if ( 0 ){
    lev1 = LOW;
    lev2 = HIGH;
  }
  digitalWrite(ledx, lev1);   // turn the LED on (HIGH is the voltage level)
  delay(100);                       // wait for a second
//  digitalWrite(ledx, lev2);    // turn the LED off by making the voltage LOW
//  delay(200);                       // wait for a second
//  digitalWrite(ledx, lev1);   // turn the LED on (HIGH is the voltage level)
//  delay(200);                       // wait for a second
  digitalWrite(ledx, lev2);    // turn the LED off by making the voltage LOW
  delay(500);                       // wait for a second
  n++;
  int vcc = ESP.getVcc();
  Serial.println(n);
  Serial.println(vcc);
}
