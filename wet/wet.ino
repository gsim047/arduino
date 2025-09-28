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
//#include <esp_sleep.h>

// Фактор для перевода секунд в микросекунды
#define uS_TO_S_FACTOR 1000000

// Время, через которое ESP32 должен проснуться (в секундах)
#define TIME_TO_SLEEP 10

const char* ssid = "HomeAsus_2";
const char* password = "atlana8312";
const char* url = "192.168.2.107/datt.php";


bool tConnect()
{
  int n = 0;
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    n++;
    Serial.print("+");
    if ( n >= 20 )
      return false;
  }
  return true;
}


void blink(int tim, int level1, int level0)
{
  digitalWrite(LED_BUILTIN, level1);   // turn the LED on (HIGH is the voltage level)
  delay(tim);                       // wait for a second
  digitalWrite(LED_BUILTIN, level0);    // turn the LED off by making the voltage LOW
  
}//


// the setup function runs once when you press reset or power the board
void setup() 
{
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(9600);
//  WiFi.begin(ssid, password);
  Serial.print("connect... ");

  int n = 0;
  while ( 0 ){
//  while ( !tConnect() ){
    if ( n >= 5 ){
      return;
    }
    n++;
    WiFi.begin(ssid, password);
    Serial.println();
    Serial.print("connect... ");
  }
  Serial.println("\nWiFi connected");
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  int lev0 = LOW;
  int lev1 = HIGH;

  if ( 1 ){
    lev0 = HIGH;
    lev1 = LOW;
  }
  blink(200, lev0, lev1);
  delay(200);                       // wait for a second
  blink(200, lev0, lev1);

  // Настройка пробуждения по таймеру
  //esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  ESP.deepSleep(15e6);

  // Вывод сообщения в последовательный порт перед засыпанием
  Serial.println("Захожу в глубокий сон...");
  Serial.flush(); // Ожидаем завершения вывода

  // Запускаем режим глубокого сна
  //esp_deep_sleep_start();
}//




// the loop function runs over and over again forever
void loop() 
{
  int lev0 = LOW;
  int lev1 = HIGH;

  if ( 1 ){
    lev0 = HIGH;
    lev1 = LOW;
  }

  /*
//  digitalWrite(LED_BUILTIN, lev0);   // turn the LED on (HIGH is the voltage level)
//  delay(200);                       // wait for a second
//  digitalWrite(LED_BUILTIN, lev1);    // turn the LED off by making the voltage LOW
  blink(200, lev0, lev1);
  delay(200);                       // wait for a second
//  digitalWrite(LED_BUILTIN, lev0);   // turn the LED on (HIGH is the voltage level)
//  delay(200);                       // wait for a second
  blink(200, lev0, lev1);
//  digitalWrite(LED_BUILTIN, lev1);    // turn the LED off by making the voltage LOW
  delay(1400);                       // wait for a second
  */

  if ( WiFi.status() == WL_CONNECTED ) {
    HTTPClient http;
    WiFiClient wc;

    if ( !wc.connect(url, 80) ) {
     // Serial.println("connection failed");
      return;
    }
    Serial.print("Requesting URL: ");
    Serial.println(url);
  
  // This will send the request to the server
//  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
//               "Host: " + host + "\r\n" + 
//               "Connection: close\r\n\r\n");
    delay(10);
  
  // Read all the lines of the reply from server and print them to Serial
    Serial.println("Respond:");
    while ( wc.available() ){
      String line = wc.readStringUntil('\r');
      Serial.print(line);
    }
  }
  
  // We now create a URI for the request
  //String url = "/stan";
  
/*    
    http.begin(WiFi, url);
        int httpCode = http.GET();

        if (httpCode > 0) {
          if (httpCode == HTTP_CODE_OK) {
            String payload = http.getString();
            Serial.println(payload);
          }
        } else {
          Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
        }
        http.end();
  }
*/
  delay(10000);

}
