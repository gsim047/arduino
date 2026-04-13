#include <Arduino.h>

#include <gmBlink.h>
#include <gmUrl.h>
#include <gmFn.h>
#include <gmTimer.h>
#include <gmCfgRead.h>



#define  SENSOR      A0


//ESP8266WiFiMulti WiFiMulti;
int n = 0;

gmBlink bl;
gmUrl url("http://192.168.1.201/esp/set.php");

gmTimer tim(100);
int toDelay = 10000;

ADC_MODE(ADC_VCC);



void setup() 
{
	bl.blink(200);
	n = 0;

	Serial_init();
	// Serial.setDebugOutput(true);

	gmUrl::WiFi_connect();
}// setup



void loop() 
{
	if ( gmUrl::WiFi_check() ){

		bl.blink(200);
		//Serial.printf(WiFiMulti.);

		Serial.print("[HTTP] begin...\n");
		//char url[256];

		url.clear();
		if ( n == 0 ){
			url.set("event", "init");
		}
		int vcc = ESP.getVcc();
		url.set("dat", vcc);
		Serial.println(url.get());
		n++;

		String res;
		int code = url.call(res);  //
		//Serial.println(res);
		String bd = gmUrl::extract(res, "<pre>", "</pre>");
		Serial.println(bd);

		gmCfgRead rd(bd);
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
		rd.get("delay", toDelay);
		rd.get("name", url.name);
	}

	Serial.println(n);
	int i1 = 0;
	if ( tim ){
		i1 = 1;
	}
	//Serial.println(vcc);


	delay(toDelay);

}// loop
