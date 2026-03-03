#include <gmUrl.h>

#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

//#ifdef ESP32 
//#include <WiFi.h> 
//#else 
//#include <ESP8266WiFi.h> 
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266HTTPClient.h>
//#endif 

// to define:
//  char ssid[];
//  char psw[];
#include <wifi_info.h>



static ESP8266WiFiMulti WiFiMulti;


void WiFi_connect()
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid, psw);
}// WiFi_connect


bool WiFi_check()
{
	if ( (WiFiMulti.run() != WL_CONNECTED) ){
		WiFi_connect();
	}

	return (WiFiMulti.run() == WL_CONNECTED);
}// WiFi_check


String WiFi_macAddress()
{
	return WiFi.macAddress();
}// WiFi_macAddress




void gmUrl::set(const String &key, const String &val)
{
	if ( param.length() != 0 ){
		param += "&";
	}
	param += key;
	param += "=";
	param += val;
}// gmUrl::set


void gmUrl::set(const String &key, int val)
{
	set(key, String(val));
}// gmUrl::set


void gmUrl::set(const String &key, float val)
{
	set(key, String(val));
}// gmUrl::set


String gmUrl::get() const
{
	String ret = url0;
	if ( param.length() != 0 ){
		ret += "?";
		ret += param;
	}
	return ret;
}// gmUrl::get


void gmUrl::clear()
{
	param = "";
}// gmUrl::clear


int gmUrl::call(String &res)
{
	res = "";
	int ret = 0;

	WiFiClient client;
	HTTPClient http;

	String url = get();
    //Serial.printf("to call => [%s]\n", url.c_str());

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
				//Serial.println(payload);
				//String body;
				//int pos1 = payload.indexOf("<pre>");
				//if ( pos1 > 0 ){
				//	int pos2 = payload.indexOf("</pre>", pos1+5);
				//	if ( pos2 > 0 ){
			  	//		body = payload.substring(pos1+5, pos2);
				//		Serial.println("body:");
				//		Serial.println(body);
				//	}
				//}
				res = payload;
				//return 0;
			}
		}else{
			//Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
			res = http.errorToString(httpCode);
			ret = 1;
		}

		http.end();

	}else{
		Serial.println("[HTTP] Unable to connect");
		res = "[HTTP] Unable to connect";
		ret = 2;
	}
	return ret;
}// gmUrl::call


String gmUrl::extract(const String &res, const String &s1, const String &s2)
{
	String body;
	int len = s1.length();
	int pos1 = res.indexOf(s1);
	if ( pos1 > 0 ){
		int pos2 = res.indexOf(s2, pos1 + len);
		if ( pos2 > 0 ){
			body = res.substring(pos1 + len, pos2);
			//Serial.println("body:");
			//Serial.println(body);
		}
	}
	return body;
}// gmUrl::extract
