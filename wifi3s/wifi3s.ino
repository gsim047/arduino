#include <Arduino.h>

#include <gmBlink.h>
#include <gmFn.h>
#include <gmCfgRead.h>
#include <gmUrlS.h>

#include "gsim047_ru.h"


#define  SENSOR      A0


//ESP8266WiFiMulti WiFiMulti;
int n = 0;

gmBlink bl;
//gmUrl url("http://192.168.1.201/esp/set.php");
//gmUrlS url("gsim047.ru", "/esp/set.php");
gmUrlS url("https://gsim047.ru/esp/set.php");
int toDelay = 30000;
String name;

//gmTimer tim(100);

ADC_MODE(ADC_VCC);


void setup() 
{
	Serial_init();
	// Serial.setDebugOutput(true);

	bl.blink(200);
	n = 0;

	url.fp = fingerprint_gsim047_ru;
	gmUrlS::WiFi_connect();
}// setup



void exec()
{
	bl.blink(200);

	Serial.print("[HTTPS] begin...\n");
	//char url[256];

	url.clear();
	if ( n == 0 ){
		url.set("event", "init");
	}
	int vcc = ESP.getVcc();
	url.set("vcc", vcc);
	
	n++;

	String res;
	int code = url.call(res);  //
	//Serial.println(res);
	String bd = gmUrlS::extract(res, "<pre>", "</pre>");
	Serial.println(bd);

	gmCfgRead rd(bd);
	rd.get("delay", toDelay);
	rd.get("name", name);
	/*
	std::map<String, String> par;
	int nn = rd.get(par);
	//Serial.printf("nn=%d\n", nn);
	if ( nn > 0 ){
		//for ( std::map<String, String>::const_iterator it = par.begin(); it != par.end(); ++it ){
		//	String out = String("[") + it->first + "]=[" + it->second + "]";
		//	Serial.println(out);
		//}

		String dl = par["delay"];
		if ( dl.length() > 0 ){
			toDelay = dl.toInt();
			Serial.printf("param delay: %d\n", toDelay);
		}
	}*/
}// exec


void loop() 
{
	if ( gmUrlS::WiFi_check() ){
		exec();
	}

	Serial.println(n);
	//Serial.println(vcc);

	delay(toDelay);

}// loop
