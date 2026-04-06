#include <gmUrlS.h>

#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>
#include <WiFiClientSecureBearSSL.h>
//#include <certs.h>

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
static String myMac = "";


void gmUrlS::WiFi_connect()
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(wifi_ssid, wifi_psw);
}// gmUrlS::WiFi_connect


bool gmUrlS::WiFi_check()
{
	if ( (WiFiMulti.run() != WL_CONNECTED) ){
		myMac = "";
		WiFi_connect();
	}

	return (WiFiMulti.run() == WL_CONNECTED);
}// gmUrlS::WiFi_check


String gmUrlS::WiFi_macAddress()
{
	if ( myMac == "" )
		myMac = WiFi.macAddress();
	return myMac;
}// gmUrlS::WiFi_macAddress




void gmUrlS::set(const String &key, const String &val)
{
	if ( param.length() != 0 ){
		param += "&";
	}
	param += key;
	param += "=";
	param += val;
}// gmUrlS::set


void gmUrlS::set(const String &key, int val)
{
	set(key, String(val));
}// gmUrlS::set


void gmUrlS::set(const String &key, float val)
{
	set(key, String(val));
}// gmUrlS::set


String gmUrlS::get() const
{
	String ret = url1;
	if ( param.length() != 0 ){
		ret += "?";
		ret += param;
	}
	return ret;
}// gmUrlS::get


void gmUrlS::clear()
{
	param = "";
}// gmUrlS::clear


int gmUrlS::call(String &res)
{
	res = "";
	int ret = 0;

    std::unique_ptr<BearSSL::WiFiClientSecure> client(new BearSSL::WiFiClientSecure);

	//WiFiClient client;
	if ( fp ){
	    client->setFingerprint(fp); //fingerprint_gsim047_ru); //fingerprint_sni_cloudflaressl_com);
	}else{
    	client->setInsecure();
	}
	
	HTTPClient https;
	set("mac", WiFi_macAddress());

	String url = get();
    //Serial.printf("to call => [%s]\n", url.c_str());

//	if ( https.begin(*client, url, gsim047_port) /*http.begin(client, url)*/ ){  // HTTP
//	String adr = "/esp/set.php?dat=1233";
//	Serial.printf("to call >> [%s] [%s]\n", gsim047_host, adr.c_str());
	if ( dbg ) Serial.printf("to call >> [%s] [%s]\n", url0.c_str(), url.c_str());
//	if ( https.begin(*client, gsim047_host, gsim047_port, adr.c_str(), true) ){  // HTTPS
	if ( https.begin(*client, url0.c_str(), port, url.c_str(), true) ){  // HTTPS

		if ( dbg ) Serial.print("[HTTPS] GET...\n");
		int httpCode = https.GET();

		// httpCode will be negative on error
		if ( httpCode > 0 ){
			// HTTP header has been send and Server response header has been handled
			if ( dbg ) Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

			// file found at server
			if ( httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY ){
				if ( dbg ) Serial.println("done..");
				String payload = https.getString();
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
			res = https.errorToString(httpCode);
			ret = 1;
		}

		https.end();

	}else{
		if ( dbg ) Serial.println("[HTTPS] Unable to connect");
		res = "[HTTPS] Unable to connect";
		ret = 2;
	}
	return ret;
}// gmUrlS::call


int gmUrlS::call()
{
	String res;
	return call(res);
}// gmUrlS::call


String gmUrlS::extract(const String &res, const String &s1, const String &s2)
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
}// gmUrlS::extract


bool gmUrlS::slice(const String &url, String &u1, String &u3, int &prt)  // https://gsim047.ru:443/esp/set.php
{
	String u = url; // buf
	String u0 = ""; // http:// https://
	//String u1 = ""; // gsim047.ru
	String u2 = ""; // :443
	//String u3 = ""; // /esp/set.php

	int pos = u.indexOf("//");
	if ( pos >= 0 ){
		u0 = u.substring(0, pos+2);    // https://
		u = u.substring(pos+2);        // gsim047.ru:443/esp/set.php
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
			u2 = "443";
			u3 = u.substring(pos2);
		}else{                         // gsim047.ru
			u1 = u;
			u2 = "443";
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
	prt = u2.toInt();

	return true;
}// gmUrlS::slice