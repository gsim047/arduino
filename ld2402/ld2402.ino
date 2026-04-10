#include <Arduino.h>
#include <SoftwareSerial.h>
#include <gmFn.h>

// Define RX and TX pins for SoftwareSerial
const int rx_pin = 13;
const int tx_pin = 15;

// Create instances
SoftwareSerial mySerial(rx_pin, tx_pin);


void setup()
{
	Serial_init();

	mySerial.begin(115200);
	Serial.printf("SoftwareSerial initialized on RX:%d, TX:%d\n", rx_pin, tx_pin);
}// setup


void loop()
{
	if ( mySerial.available() ){
		// Read raw data from radar
		String data = mySerial.readStringUntil('\n');
		Serial.println(data); // Print to Serial Monitor
	}
	delay(50);
}// loop
