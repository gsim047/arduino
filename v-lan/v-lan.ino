#include <Arduino.h>

//#include <DHT_U.h>
//#include <DHT.h>

#include <gmUrl.h>
//#include <gmUrlS.h>
//#include "gsim047_ru.h"
#include <gmCfgRead.h>
#include <gmFn.h>
#include <gmBlink.h>


//#define SENSOR	A0

gmUrl url("http://192.168.1.201/esp/set.php");
int n = 0;
int toDelay = 10000;
String name;
gmBlink bl;
int toBlink = 1;

ADC_MODE(ADC_VCC);



void setup() 
{
	bl.blink(200);
	Serial_init();
	n = 0;

	bl.blink(200);
	Serial.println("wifi connect...");
	url.WiFi_connect();
	Serial.println("wifi!");
	bl.blink(500);
}// setup


void loop() 
{
	if ( url.WiFi_check() ){
		if ( toBlink )
			bl.blink(100);

		Serial.println("wifi ok");
		url.clear();
		if ( n == 0 ){
			url.set("event", "init");
		}
		int vcc = ESP.getVcc();
		url.set("vcc", vcc);
		url.set("name", name);

		n++;

//		String res;
		int code = url.call();  //
		//Serial.println(res);
		if ( code == 0 ){
			gmCfgRead rd(url);
			rd.get("delay", toDelay);
			//rd.get("name", name);
			rd.get("blink", toBlink);
		}
		Serial.printf("%d: %d\n", n, vcc);
	}else{
		Serial.println("NO wifi!!!");
		if ( toBlink )
			bl.blink(1000);
	}

	delay(toDelay);
}// loop

