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
		WiFi_connect();
	}

	return (WiFiMulti.run() == WL_CONNECTED);
}// gmUrlS::WiFi_check


String gmUrlS::WiFi_macAddress()
{
	return WiFi.macAddress();
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

	String url = get();
    //Serial.printf("to call => [%s]\n", url.c_str());

//	if ( https.begin(*client, url, gsim047_port) /*http.begin(client, url)*/ ){  // HTTP
//	String adr = "/esp/set.php?dat=1233";
//	Serial.printf("to call >> [%s] [%s]\n", gsim047_host, adr.c_str());
	Serial.printf("to call >> [%s] [%s]\n", url0.c_str(), url.c_str());
//	if ( https.begin(*client, gsim047_host, gsim047_port, adr.c_str(), true) ){  // HTTPS
	if ( https.begin(*client, url0.c_str(), port, url.c_str(), true) ){  // HTTPS

		Serial.print("[HTTPS] GET...\n");
		int httpCode = https.GET();

		// httpCode will be negative on error
		if ( httpCode > 0 ){
			// HTTP header has been send and Server response header has been handled
			Serial.printf("[HTTPS] GET... code: %d\n", httpCode);

			// file found at server
			if ( httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY ){
				Serial.println("done..");
				String payload = https.getString();
				Serial.println(payload);
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
		Serial.println("[HTTPS] Unable to connect");
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
