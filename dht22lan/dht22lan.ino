#include <Arduino.h>

#include <DHT_U.h>
//#include <DHT.h>

#include <gmUrl.h>
//#include <gmUrlS.h>
//#include "gsim047_ru.h"
#include <gmCfgRead.h>
#include <gmFn.h>
#include <gmBlink.h>


#define SENSOR	A0
//#define DHTTYPE	DHT11
//#define DHTPIN 2

//DHT dht(DHTPIN, DHTTYPE);

gmUrl url("http://192.168.1.201/esp/set.php");
int n = 0;
gmBlink bl;
int toDelay = 10000;

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

DHT_Unified dht(DHTPIN, DHTTYPE);

ADC_MODE(ADC_VCC);



void setup() 
{
	bl.blink(200);
	Serial_init();
	// Serial.setDebugOutput(true);

	n = 0;

//	url.fp = fingerprint_gsim047_ru;
	url.WiFi_connect();

	dht.begin();
	Serial.println(F("DHTxx Unified Sensor Example"));
	// Print temperature sensor details.
	sensor_t sensor;
	dht.temperature().getSensor(&sensor);
	Serial.println(F("------------------------------------"));
	Serial.println(F("Temperature Sensor"));
	Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
	Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
	Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
	Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
	Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
	Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
	Serial.println(F("------------------------------------"));
	// Print humidity sensor details.
	dht.humidity().getSensor(&sensor);
	Serial.println(F("Humidity Sensor"));
	Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
	Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
	Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
	Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
	Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
	Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
	Serial.println(F("------------------------------------"));
}// setup



void loop() 
{
	if ( url.WiFi_check() ){

		//bl.blink(200);
		//Serial.printf(WiFiMulti.);

		Serial.print("[HTTPS] begin...\n");
		//char url[256];

		url.clear();
		if ( n == 0 ){
//			String mac = url.WiFi_macAddress();
			url.set("dat", "init");
//			url.set("mac", mac);
			//sprintf(url, "/esp/set1.php?dat=init&mac=%s", mac.c_str());
		}else{

			sensors_event_t event;
			dht.temperature().getEvent(&event);
			if ( isnan(event.temperature) ){
				url.set("t", "error");
			}else{
				url.set("t", event.temperature);
			}

  // Get humidity event and print its value.
			dht.humidity().getEvent(&event);
			if ( isnan(event.relative_humidity) ){
				url.set("h", "error");
			}else{
				url.set("h", event.relative_humidity);
			}
		}
		Serial.println(url.get());
		n++;

		int code = url.call();  //
		//Serial.println(res);
		//String bd = url.extract(res, "<pre>", "</pre>");
		//Serial.println(bd);

		gmCfgRead rd(url);
		rd.get("delay", toDelay);
	}

	Serial.println(n);

	delay(toDelay);

}// loop
