#include <gmNetTools.h>

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
