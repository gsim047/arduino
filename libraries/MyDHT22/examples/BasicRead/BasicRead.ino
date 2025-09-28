/*
  BasicRead.ino - Basic example for reading temperature and humidity using DHT22
  Library: MyDHT22 by Fadhil
  Board: Arduino UNO / Nano

  Wiring:
  - DHT22 DATA pin connected to digital pin 2
  - Use a 10kΩ pull-up resistor between DATA and VCC
*/

#include <MyDHT22.h>  // Include the MyDHT22 library

// Create a DHT22 sensor object on pin D2
MyDHT22 dht(2);

void setup() {
  Serial.begin(9600);  // Start the serial communication at 9600 baud
}

void loop() {
  // Read the sensor data
  dht.readData();

  // Print temperature in Celsius
  Serial.print("Temperature: ");
  Serial.print(dht.getTemperature());
  Serial.print(" °C, ");

  // Print humidity in percentage
  Serial.print("Humidity: ");
  Serial.print(dht.getHumidity());
  Serial.println(" %");

  // Wait 2 seconds before the next reading
  delay(2000);
}
