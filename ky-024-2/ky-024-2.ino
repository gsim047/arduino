#include <Arduino.h>
//#include <OneWire.h>
//#include <DallasTemperature.h>
#include <gmUrlS.h>
//#include <wifi_info.h>
#include <gmFn.h>


#define DPIN 4
// A0 - 17
#define APIN A0

int n = 0;
float last = 0.;
int step = 5;

gmUrlS url("https://gsim047.ru/esp/set.php");



void setup() 
{
	setWiFi(0);
	//Serial.begin(115200);
	pinMode(DPIN, INPUT);
	pinMode(APIN, INPUT);
  
    Serial_init();
	//Serial.println("\nStart!");
	n = 0;
	url.WiFi_connect();
}// setup


void loop() 
{
	if ( !url.WiFi_check() ){
		delay(500);
		return;
	}

	n++;
	int dres = digitalRead(DPIN);
	float ares = analogRead(APIN);

	float dl = 0.;
	if ( ares > last )
		dl = ares - last;
	else
		dl = last - ares;

	if ( dl >= step ){
		Serial.printf("%d: %d %.0f\n", n, dres, ares);

		url.clear();
		url.set("n", n);
//		url.set("mac", url.WiFi_macAddress());
		url.set("d", dres);
		url.set("a", ares);

		//String res;
		int ret = url.call(); //res);
	}

	n++;
	last = ares;
	delay(100);
}// loop
