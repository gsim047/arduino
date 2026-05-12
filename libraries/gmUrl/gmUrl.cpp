#include <gmUrl.h>

#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>

#include <gmCfgRead.h>

//#ifdef ESP32 
//#include <WiFi.h> 
//#else 
//#include <ESP8266WiFi.h> 
//#include <ESP8266WiFiMulti.h>
//#include <ESP8266HTTPClient.h>
//#endif 

// to define:
//  char *wifi_ssid;
//  char *wifi_psw;
#include <wifi_info.h>



static ESP8266WiFiMulti WiFiMulti;


void gmUrl::WiFi_connect()
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(wifi_ssid, wifi_psw);
}// gmUrl::WiFi_connect


bool gmUrl::WiFi_check()
{
	if ( (WiFiMulti.run() != WL_CONNECTED) ){
		WiFi_connect();
	}

	return (WiFiMulti.run() == WL_CONNECTED);
}// gmUrl::WiFi_check


String gmUrl::WiFi_macAddress()
{
	return WiFi.macAddress();
}// gmUrl::WiFi_macAddress




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
	if ( dbg ) Serial.printf("url 0:[%s] 1:[%s] p:[%d]\n", url0.c_str(), url1.c_str(), port);
	String ret = "http://" + url0;
	if ( port > 0 ){
		ret += ":" + String(port);
	}
	ret += "/" + url1;
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


int gmUrl::call()
{
	res = "";
	int ret = 0;

	WiFiClient client;
	HTTPClient http;

	set("mac", WiFi_macAddress());
	set("name", name);

	String url = get();
	if ( dbg ) Serial.printf("to call => [%s]\n", url.c_str());

	if ( http.begin(client, url) ){  // HTTP

		if ( dbg ) Serial.print("[HTTP] GET...\n");
		int httpCode = http.GET();

		// httpCode will be negative on error
		if ( httpCode > 0 ){
			// HTTP header has been send and Server response header has been handled
			if ( dbg ) Serial.printf("[HTTP] GET... code: %d\n", httpCode);

			// file found at server
			if ( httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY ){
				if ( dbg ) Serial.println("done..");
				String payload = http.getString();
				if ( dbg ) Serial.println(payload);
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
		if ( dbg ) Serial.println("[HTTP] Unable to connect");
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


bool gmUrl::slice(const String &url, String &pr, String &u1, String &u3, int &prt)  // https://gsim047.ru:443/esp/set.php
{
	String u = url; // buf
	String u0 = ""; // http:// https://
	//String u1 = ""; // gsim047.ru
	String u2 = ""; // :443
	//String u3 = ""; // /esp/set.php

	int pos = u.indexOf("//");
	if ( pos >= 0 ){
		u0 = u.substring(0, pos+2);    // https://
		pr = u0;
		u = u.substring(pos+2);        // gsim047.ru:443/esp/set.php
	}else{
		pr = ""; // ??? http:// ?
	}

	int pos1 = u.indexOf(":");
	if ( pos1 >= 0 ){
		u1 = u.substring(0, pos1);     // gsim047.ru
		u = u.substring(pos1+1);       // :443/esp/set.php

		int pos2 = u.indexOf("/");
		if ( pos2 >= 0 ){
			u2 = u.substring(0, pos2); // 443
			u = u.substring(pos2+1);   // /esp/set.php
		}else{                         // gsim047.ru:443
			u2 = u.substring(0);       // 443
			u = "";
		}
	}else{                             // gsim047.ru/esp/set.php
		int pos2 = u.indexOf("/");
		if ( pos2 >= 0 ){              // gsim047.ru/esp/set.php
			u1 = u.substring(0, pos2);
			u2 = "";
			u3 = u.substring(pos2);
		}else{                         // gsim047.ru
			u1 = u;
			u2 = "";
			u3 = "/";
		}
	}

	pos = u3.indexOf("?");
	if ( pos >= 0 ){
		u3 = u3.substring(0, pos);
	}

	//Serial.println("url: " + url);
	//Serial.println("u0: " + u0);
	//Serial.println("u1: " + u1);
	//Serial.println("u2: " + u2);
	//Serial.println("u3: " + u3);
	if ( u2 != "" ){
		prt = u2.toInt();
	}else{
		prt = 0;
	}

	return true;
}// gmUrl::slice


void gmUrl::init()
{
	WiFi_connect();

	for ( int i = 0; i < 16; i++ ){
		if ( WiFi_check() )
			break;
		delay(250);
	}

   	clear();
   	set("event", "init");
	int code = call();  //
	if ( code == 0 ){
		gmCfgRead rd(*this);
		//rd.get("name", name);
	}
}// gmUrl::init

