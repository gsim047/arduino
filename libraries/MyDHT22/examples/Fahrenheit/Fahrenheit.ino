/*
  FahrenheitRead.ino - Example for reading temperature in Fahrenheit from DHT22
  Library: MyDHT22 by Fadhil
  Board: Arduino UNO / Nano

  Wiring:
  - DHT22 DATA pin connected to digital pin 2
  - Use a 10kΩ pull-up resistor between DATA and VCC
*/

#include <MyDHT22.h>  // Include the MyDHT22 library

// Create a DHT22 sensor object on pin D2
MyDHT22 dht(2);

// Convert Celsius to Fahrenheit
float toFahrenheit(float celsius) {
  return (celsius * 9.0 / 5.0) + 32;
}

void setup() {
  Serial.begin(9600);  // Start serial communication
}

void loop() {
  // Read sensor and proceed only if successful
  if (dht.readData()) {
    float tempC = dht.getTemperature();
    float tempF = toFahrenheit(tempC);

    Serial.print("Temperature: ");
    Serial.print(tempF);
    Serial.print(" °F, Humidity: ");
    Serial.print(dht.getHumidity());
    Serial.println(" %");
  } else {
    Serial.println("Sensor error");
  }

  delay(2000); // Wait 2 seconds before next reading
}
