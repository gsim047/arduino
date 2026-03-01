
#include <gmNetTools.h>
//#include <Arduino.h>

//#ifdef ESP32 
//#include <WiFi.h> 
//#else 
//#include <ESP8266WiFi.h> 
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266HTTPClient.h>
//#endif 

//#include <WiFiClient.h>
//void setup(){ Serial.begin(115200); Serial.println(); Serial.print("ESP Board MAC Address: "); Serial.println(WiFi.macAddress()); } void loop(){ }

#include "/home/user/Arduino/wifi_info.h"


//extern ESP8266WiFiMulti WiFiMulti;



void WiFiConnect(ESP8266WiFiMulti &WiFiMulti)
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid, psw);
}// WiFiConnect



String callUrl(const char *url1)
{
	WiFiClient client;
	HTTPClient http;

	char url[256];
	sprintf(url, "%s", url1);
    Serial.printf("to call => [%s]\n", url);

	if ( http.begin(client, url) ){  // HTTP


		Serial.print("[HTTP] GET...\n");
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
				return payload;
			}
		}else{
			Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
		}

		http.end();

	}else{
		Serial.println("[HTTP] Unable to connect");
	}
	return "";
}// callUrl

