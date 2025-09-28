/**
   BasicHTTPClient.ino

    Created on: 24.05.2015

*/

#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#define  SENSOR      A0


ESP8266WiFiMulti WiFiMulti;


void WiFiConnect()
{
  if ( (WiFiMulti.run() == WL_CONNECTED) ) {
    return;
  }
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("HomeAsus_2", "atlana8312");
}//


void blink(int tim, int level1, int level0)
{
  digitalWrite(LED_BUILTIN, level1);   // turn the LED on (HIGH is the voltage level)
  delay(tim);                       // wait for a second
  digitalWrite(LED_BUILTIN, level0);    // turn the LED off by making the voltage LOW
  
}//


void setup() 
{
  Serial.begin(9600);
  // Serial.setDebugOutput(true);
  pinMode(LED_BUILTIN, OUTPUT);
  blink(200, LOW, HIGH);


  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  //WiFi.mode(WIFI_STA);
  //WiFiMulti.addAP("HomeAsus_2", "atlana8312");
  WiFiConnect();
}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() != WL_CONNECTED)) {
    WiFiConnect();
  }
  
  if ((WiFiMulti.run() == WL_CONNECTED)) {
    //Serial.printf(WiFiMulti.);

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    if ( http.begin(client, "http://192.168.2.107") ){  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println("444");
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
  }

  delay(10000);
}
