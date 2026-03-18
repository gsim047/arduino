#include <Arduino.h>

#define  SENSOR      A0


// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600); 

}//


void blink(int tim, int level1, int level0)
{
  digitalWrite(LED_BUILTIN, level1);   // turn the LED on (HIGH is the voltage level)
  delay(tim);                       // wait for a second
  digitalWrite(LED_BUILTIN, level0);    // turn the LED off by making the voltage LOW
  
}//


// the loop function runs over and over again forever
void loop() 
{
  int lev0 = LOW;
  int lev1 = HIGH;

  if ( 0 ){
    lev0 = HIGH;
    lev1 = LOW;
  }

  uint16_t sensor = analogRead(SENSOR);    // Читаем данные с датчика,
  Serial.println(sensor);
  
//  digitalWrite(LED_BUILTIN, lev0);   // turn the LED on (HIGH is the voltage level)
//  delay(200);                       // wait for a second
//  digitalWrite(LED_BUILTIN, lev1);    // turn the LED off by making the voltage LOW
  blink(200, lev0, lev1);
  delay(200);                       // wait for a second
//  digitalWrite(LED_BUILTIN, lev0);   // turn the LED on (HIGH is the voltage level)
//  delay(200);                       // wait for a second
  blink(200, lev0, lev1);
//  digitalWrite(LED_BUILTIN, lev1);    // turn the LED off by making the voltage LOW
  delay(1400);                       // wait for a second

}
