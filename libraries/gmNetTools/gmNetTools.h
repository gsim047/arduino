#ifndef __gmNetTools_h
#define __gmNetTools_h 1

#include <Arduino.h>

#include <ESP8266WiFi.h> 
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#include <WiFiClient.h>


void WiFiConnect(ESP8266WiFiMulti &WiFiMulti);

String callUrl(const char *url1);

#endif // __gmNetTools_h
