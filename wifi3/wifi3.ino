
#include <Arduino.h>
#include <gmBlink.h>

//#include <gmNetTools.h>
#include <gmUrl.h>
#include <gmTimer.h>
#include <gmCfgRead.h>



#define  SENSOR      A0


//ESP8266WiFiMulti WiFiMulti;
int n = 0;

gmBlink bl;
gmUrl url("http://192.168.1.201/esp/set.php");

gmTimer tim(100);

//int ledN = LED_BUILTIN;
//int ledINV = 1;
//char ssid[] = "HomeAsus87U";
//char psw[] = "***";
//char url0[] = "http://192.168.1.201";

ADC_MODE(ADC_VCC);



void setup() 
{
	Serial.begin(115200);
	// Serial.setDebugOutput(true);

	bl.blink(200);
	n = 0;

	Serial.println();
	Serial.println();
	Serial.println();

	for ( int t = 4; t > 0; t-- ){
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}

	WiFi_connect();
}// setup



int toDelay = 10000;


void loop() 
{
	if ( WiFi_check() ){

		bl.blink(200);
		//Serial.printf(WiFiMulti.);

		Serial.print("[HTTP] begin...\n");
		//char url[256];

		url.clear();
		if ( n == 0 ){
			String mac = WiFi_macAddress();
			url.set("dat", "init");
			url.set("mac", mac);
			//sprintf(url, "/esp/set1.php?dat=init&mac=%s", mac.c_str());
		}else{
			int vcc = ESP.getVcc();
			url.set("dat", vcc);
			//sprintf(url, "/esp/set1.php?dat=%d", vcc);
		}
		Serial.println(url.get());
		n++;

		String res;
		int code = url.call(res);  //
		//Serial.println(res);
		String bd = gmUrl::extract(res, "<pre>", "</pre>");
		Serial.println(bd);

		gmCfgRead rd(bd);
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
		}
	}

	Serial.println(n);
	int i1 = 0;
	if ( tim ){
		i1 = 1;
	}
	//Serial.println(vcc);


	delay(toDelay);

}// loop
