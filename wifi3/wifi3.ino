/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>
#include <gmBlink.h>

#ifdef ESP32 
#include <WiFi.h> 
#else 
#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#endif 


#include <WiFiClient.h>

#include <gmNetTools.h>
#include <gmUrl.h>
#include <gmTimer.h>
#include <gmCfgRead.h>

//void setup(){ Serial.begin(115200); Serial.println(); Serial.print("ESP Board MAC Address: "); Serial.println(WiFi.macAddress()); } void loop(){ }

//#include "/home/user/Arduino/wifi_info.h"

#define  SENSOR      A0


ESP8266WiFiMulti WiFiMulti;
int n = 0;

gmBlink bl;
gmUrl url("http://192.168.1.201/esp/set1.php");

//int ledN = LED_BUILTIN;
//int ledINV = 1;
//char ssid[] = "HomeAsus87U";
//char psw[] = "***";
//char url0[] = "http://192.168.1.201";

//int levLOW = LOW;
//int levHIGH = HIGH;

ADC_MODE(ADC_VCC);



//void WiFiConnect();
/*
static void WiFiConnect()
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid, psw);
}// WiFiConnect
*/
/*
static void blink(int tim, int level1, int level0)
{
	digitalWrite(ledN, level1);   // turn the LED on (HIGH is the voltage level)
	delay(tim);                       // wait for a second
	digitalWrite(ledN, level0);    // turn the LED off by making the voltage LOW
}// blink
*/

void setup() 
{
	Serial.begin(115200);
	// Serial.setDebugOutput(true);
	//pinMode(ledN, OUTPUT);

	//if ( ledINV ){
	//	levLOW = HIGH;
	//	levHIGH = LOW;
	//}

	//blink(200, levLOW, levHIGH);
	bl.bl(200);
	n = 0;

	Serial.println();
	Serial.println();
	Serial.println();

	for ( int t = 4; t > 0; t-- ){
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}

	WiFiConnect(WiFiMulti);
}// setup


//void callUrl(const char *url);
/*
static void callUrl(const char *url)
{
	WiFiClient client;
	HTTPClient http;

	if ( http.begin(client, url) ){  // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if ( httpCode > 0 ){
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if ( httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY ){
        Serial.println("done..");
        String payload = http.getString();
        Serial.println(payload);
        String body;
        int pos1 = payload.indexOf("<pre>");
        if ( pos1 > 0 ){
	        int pos2 = payload.indexOf("</pre>", pos1+5);
			if ( pos2 > 0 ){
        		body = payload.substring(pos1+5, pos2);
                Serial.println("body:");
                Serial.println(body);
            }
        }
      }
    }else{
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
    blink(200, LOW, HIGH);

	}else{
		Serial.println("[HTTP] Unable to connect");
	}
}// callUrl
*/

void loop() 
{
	// wait for WiFi connection
	WiFiConnect(WiFiMulti);
  
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		bl.bl(200);
		//Serial.printf(WiFiMulti.);

//		WiFiClient client;
//		HTTPClient http;

		Serial.print("[HTTP] begin...\n");
		//char url[256];

		url.clear();
		if ( n == 0 ){
			String mac = WiFi.macAddress();
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
		Serial.println(res);
		String bd = gmUrl::extract(res, "<pre>", "</pre>");

		gmCfgRead rd(bd);
		std::map<String, String> par;
		int err = rd.get(par);

/*    
    if ( http.begin(client, url) ){  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println("done..");
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();
      blink(200, LOW, HIGH);

    } else {
      Serial.println("[HTTP] Unable to connect");
    }
    */
  }

	Serial.println(n);
	//Serial.println(vcc);


	delay(10000);

}// loop
