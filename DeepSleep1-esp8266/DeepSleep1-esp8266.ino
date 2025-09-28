/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
//#include "c_types.h"
#include <NTPClient.h>
#include <WiFiUdp.h>


void ledx(int lev1, int lev2, int tim)
{
  digitalWrite(LED_BUILTIN, lev1);   // turn the LED on (HIGH is the voltage level)
  delay(tim);                       // wait for a second
  digitalWrite(LED_BUILTIN, lev2);    // turn the LED off by making the voltage LOW
}


int lev1 = HIGH;
int lev2 = LOW;

#define  SENSOR      A0


const char* ssid = "HomeAsus_2";
const char* password = "atlana8312";
//const char* url = "192.168.2.107/datt.php";

/*
bool tConnect()
{
  int n = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    n++;
    Serial.print("+");
    if ( n >= 10 )
      return false;
  }
  return true;
}



static uint32 *rtc = (uint32 *)0x60000700;

void nk_deepsleep(uint32 time_us) {
  rtc[0] = 0x30;
  rtc[1] = rtc[7] + 5;
  rtc[3] = 0x10010;
  rtc[4] = 0;
  rtc[6] = 8;
  rtc[17] = 4;
  rtc[2] = 1 << 20;
  ets_delay_us(10);
  rtc[0] &= 0xFCF;
  rtc[0] = 0;
  rtc[1] = rtc[7] + (45 * (time_us >> 8));
  rtc[3] = 0x640C8;
  rtc[6] = 0x18;
  rtc[16] = 0x7F;
  rtc[17] = 0x20;
  rtc[39] = 0x11;
  rtc[40] = 0x03;
  rtc[2] = 1 << 20;
  __asm volatile("waiti 0");
}
*/


// the setup function runs once when you press reset or power the board
void setup() {
  char buf[256];
  Serial.begin(74880);
  Serial.setTimeout(2000);

  Serial.println("\n\nwake up");

  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  //pinMode(D0, WAKEUP_PULLUP);

  Serial.println("send call...");
  if ( 1 ){
    lev1 = LOW;
    lev2 = HIGH;
  }
//  Serial.println("3");

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());

//  WiFiUDP udp;
  // Время в миллисекундах (NTPClient(udp, "pool.ntp.org", offset_sec, interval_ms))
  //NTPClient timeClient(udp, "pool.ntp.org", 3 * 3600, 60000); 
//  NTPClient timeClient(udp);
//  timeClient.begin();
//  delay(200);
//  timeClient.update(); // Обновляем время
//  delay(200);
//  timeClient.update(); // Обновляем время
//  Serial.println(timeClient.getFormattedTime());
  
  uint16_t sensor = analogRead(SENSOR);    // Читаем данные с датчика,

  sprintf(buf, "http://192.168.2.107/datt.php?dat=%d", sensor);
  Serial.print("dat: [");
  Serial.print(buf);
  Serial.println("]");

    WiFiClient client;
    HTTPClient http;
    if ( http.begin(client, buf) ){  // HTTP

      int httpCode = http.GET();

      // httpCode will be negative on error
      //if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        //if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        //  String payload = http.getString();
        //  Serial.println(payload);
        //}
      //} else {
      //  Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      //}

      http.end();
      //Serial.println("done");
    }
  
  ledx(lev1, lev2, 200);
  //delay(200);                       // wait for a second
  //ledx(lev1, lev2, 200);
  delay(1000);                       // wait for a second
  Serial.println("...sleeeeep...");

  ESP.deepSleep(3600 * 1000000);
  //nk_deepsleep(10000000);
  //Serial.println("5");
  delay(10);
  //Serial.println("6");

}


// the loop function runs over and over again forever
void loop() {
  
//  ledx(lev1, lev2, 100);
//  delay(200);                       // wait for a second
//  ledx(lev1, lev2, 100);
//  delay(1000);                       // wait for a second
/*
  digitalWrite(LED_BUILTIN, lev1);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, lev2);    // turn the LED off by making the voltage LOW
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, lev1);   // turn the LED on (HIGH is the voltage level)
  delay(200);                       // wait for a second
  digitalWrite(LED_BUILTIN, lev2);    // turn the LED off by making the voltage LOW
  delay(1000); */                      // wait for a second
}
