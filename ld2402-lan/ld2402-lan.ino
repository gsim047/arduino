#include <Arduino.h>
#include <SoftwareSerial.h>
#include <gmFn.h>
#include <gmStep.h>
#include <gmUrl.h>
#include <gmCfgRead.h>

// Define RX and TX pins for SoftwareSerial
const int rx_pin = 13;
const int tx_pin = 15;

gmStep st(20);
gmUrl url("http://192.168.1.201/esp/dist/set.php");
// Create instances
SoftwareSerial mySerial(rx_pin, tx_pin);



void setup()
{
	Serial_init();

	mySerial.begin(115200);
	Serial.printf("SoftwareSerial initialized on RX:%d, TX:%d\n", rx_pin, tx_pin);

	//url.dbg = 1;
	url.init();
	/*
	url.WiFi_connect();

	for ( int i = 0; i < 16; i++ ){
		if ( url.WiFi_check() )
			break;
		delay(250);
	}

   	url.clear();
   	url.set("event", "init");
	int code = url.call();  //
	if ( code == 0 ){
		gmCfgRead rd(url);
		//rd.get("name", name);
	}*/
}// setup


void loop()
{
	if ( mySerial.available() ){
		// Read raw data from radar
		String data = mySerial.readStringUntil('\n');
		int pos = data.indexOf(":");
		if ( pos > 0 ){
			String data1 = data.substring(pos+1);
			int d = data1.toInt();
			if ( d > 0 ){
				st = d;
				if ( st.changed() ){
					url.clear();
					url.set("dist", d);
					url.call();
					Serial.println(st.val); // Print to Serial Monitor
				}
			}
		}
	}
	delay(50);
}// loop
