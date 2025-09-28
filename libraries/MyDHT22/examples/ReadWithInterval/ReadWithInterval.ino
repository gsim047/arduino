/*
  TimedRead.ino - Non-blocking example for reading DHT22 every 5 seconds
  Library: MyDHT22 by Fadhil
  Board: Arduino UNO / Nano

  Description:
  - Uses millis() instead of delay() to perform non-blocking sensor reading.
  - Useful when you need to do other tasks in loop() without delay interference.

  Wiring:
  - DHT22 DATA pin connected to digital pin 2
  - Use a 10kΩ pull-up resistor between DATA and VCC
*/

#include <MyDHT22.h>  // Include the MyDHT22 library

// Create a DHT22 sensor object on pin D2
MyDHT22 dht(2);

// Time tracking variables
unsigned long lastRead = 0;
const unsigned long interval = 5000;  // Read every 5 seconds

void setup() {
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  // Check if 5 seconds have passed since last reading
  if (millis() - lastRead >= interval) {
    lastRead = millis();  // Update last read time

    if (dht.readData()) {
      Serial.print("Temperature: ");
      Serial.print(dht.getTemperature());
      Serial.print(" °C, Humidity: ");
      Serial.print(dht.getHumidity());
      Serial.println(" %");
    } else {
      Serial.println("Read error.");
    }
  }

  // Other non-blocking tasks can be performed here
}
