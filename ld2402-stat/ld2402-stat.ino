#include <Arduino.h>
#include <SoftwareSerial.h>
#include <gmFn.h>
#include <gmStat.h>

// Define RX and TX pins for SoftwareSerial
const int rx_pin = 13;
const int tx_pin = 15;

// Create instances
SoftwareSerial mySerial(rx_pin, tx_pin);
int n = 0;
gmStat s(0, 1000, 50);


void setup()
{
	Serial_init();

	mySerial.begin(115200);
	Serial.printf("SoftwareSerial initialized on RX:%d, TX:%d\n", rx_pin, tx_pin);

	n = 0;
}// setup


void loop()
{
	//int val = 0;
	if ( mySerial.available() ){
		// Read raw data from radar
		String data = mySerial.readStringUntil('\n');
		//Serial.println(data); // Print to Serial Monitor
		int idx = data.indexOf(":");
		if ( idx > 0 ){
			String sval = data.substring(idx+1);
			int val = sval.toInt();
			//if ( val > 0 && val < 1000 ){
			//}
			s += val;
		}
	}
	n++;
	if ( s.size() >= 50 ){
		String out;
		for ( std::map<int, int>::const_iterator it = s.nn.begin(); it != s.nn.end(); ++it ){
			int key = it->first;
			int val = it->second;
			if ( val > 0 ){
				out += String(key) + ":" + String(val) + ", ";
			}
		}
		out += " middle:: " + String(s.middle());
		Serial.println(out);
		s.clear();
		n = 0;
	}
	delay(50);
}// loop
