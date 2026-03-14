#include <Arduino.h>

#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>

#include <string>
using std::string;
#include <map>

string de23;
std::map<string, string> qwerty;

#define DHTPIN 2     // Digital pin connected to the DHT sensor 
// Feather HUZZAH ESP8266 note: use pins 3, 4, 5, 12, 13 or 14 --
// Pin 15 can work but DHT must be disconnected during program upload.

// Uncomment the type of sensor in use:
//#define DHTTYPE    DHT11     // DHT 11
#define DHTTYPE    DHT22     // DHT 22 (AM2302)

//#define SENSOR	A0

DHT_Unified dht(DHTPIN, DHTTYPE);

ESP8266WiFiMulti WiFiMulti;

int n = 0;
char ssid[] = "HomeAsus_X";
char psw[] = "atlana8312";
char url0[] = "http://192.168.1.201";

ADC_MODE(ADC_VCC);



void WiFiConnect()
{
	if ( (WiFiMulti.run() == WL_CONNECTED) ){
		return;
	}
	Serial.println("connecting...");
	WiFi.mode(WIFI_STA);
	WiFiMulti.addAP(ssid, psw);
}// WiFiConnect


void blink(int tim, int level1, int level0)
{
	digitalWrite(LED_BUILTIN, level1);    // turn the LED on (HIGH is the voltage level)
	delay(tim);                           // wait for a second
	digitalWrite(LED_BUILTIN, level0);    // turn the LED off by making the voltage LOW
}// blink


void setup() 
{
  Serial.begin(115200);
  // Serial.setDebugOutput(true);
  pinMode(LED_BUILTIN, OUTPUT);
//  Wire.begin(4, 5);
  blink(200, LOW, HIGH);
  pinMode(0, INPUT);
  n = 0;


  Serial.println();
  Serial.println();
  Serial.println();

  for (uint8_t t = 4; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }
  //dht.begin();

  WiFiConnect();
  Serial.println("WiFi connected");
  //bmp.begin();
  //Serial.println("bmp180 inited");

  dht.begin();
  Serial.println(F("DHTxx Unified Sensor Example"));
  // Print temperature sensor details.
  sensor_t sensor;
  dht.temperature().getSensor(&sensor);
  Serial.println(F("------------------------------------"));
  Serial.println(F("Temperature Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("°C"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("°C"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("°C"));
  Serial.println(F("------------------------------------"));
  // Print humidity sensor details.
  dht.humidity().getSensor(&sensor);
  Serial.println(F("Humidity Sensor"));
  Serial.print  (F("Sensor Type: ")); Serial.println(sensor.name);
  Serial.print  (F("Driver Ver:  ")); Serial.println(sensor.version);
  Serial.print  (F("Unique ID:   ")); Serial.println(sensor.sensor_id);
  Serial.print  (F("Max Value:   ")); Serial.print(sensor.max_value); Serial.println(F("%"));
  Serial.print  (F("Min Value:   ")); Serial.print(sensor.min_value); Serial.println(F("%"));
  Serial.print  (F("Resolution:  ")); Serial.print(sensor.resolution); Serial.println(F("%"));
  Serial.println(F("------------------------------------"));
}


void callUrl(const char *url)
{
  WiFiClient client;
  HTTPClient http;

  if ( http.begin(client, url) ){  // HTTP


    Serial.print("[HTTP] GET...\n");
    // start connection and send HTTP header
    int httpCode = http.GET();

    // httpCode will be negative on error
    if (httpCode > 0) {
      // HTTP header has been send and Server response header has been handled
      Serial.printf("[HTTP] GET... code: %d\n", httpCode);

      // file found at server
      if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
        Serial.println("done..");
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
}// callUrl


void loop() {
  // wait for WiFi connection
  if ( (WiFiMulti.run() != WL_CONNECTED) ){
    Serial.println("to connect...");
    WiFiConnect();
  }
  
  if ( (WiFiMulti.run() == WL_CONNECTED) ){
    //Serial.printf(WiFiMulti.);

    WiFiClient client;
    HTTPClient http;

    Serial.print("[HTTP] begin...\n");
    char url[256];

    if ( n == 0 ){
    	sprintf(url, "%s/esp/set1.php?dat=init", url0);
    }else{
    	//float t = 0.; //dht.readTemperature();
      //float h = 0.; //dht.readHumidity();
      //bmp.getTemperature(&t);
//    	int vcc = ESP.getVcc();
//    	sprintf(url, "%s/esp/set1.php?dat=t-%d", url0, vcc);

        {
  sensors_event_t event;
  dht.temperature().getEvent(&event);
  if (isnan(event.temperature)) {
    Serial.println(F("Error reading temperature!"));
    sprintf(url, "%s/esp/set1.php?error=temperature", url0);
  }
  else {
    Serial.print(F("Temperature: "));
    Serial.print(event.temperature);
    Serial.println(F("°C"));
    sprintf(url, "%s/esp/set1.php?t=%f", url0, event.temperature);
  }
  // Get humidity event and print its value.
  dht.humidity().getEvent(&event);
  if ( isnan(event.relative_humidity) ){
    Serial.println(F("Error reading humidity!"));
    sprintf(url, "%s/esp/set1.php?error=humidity", url0);
  }else{
    Serial.print(F("Humidity: "));
    Serial.print(event.relative_humidity);
    Serial.println(F("%"));
    sprintf(url, "%s/esp/set1.php?h=%f", url0, event.relative_humidity);

  }
        }
    }
    Serial.println(url);
    n++;
    callUrl(url);

/*    
    if ( http.begin(client, url) ){  // HTTP


      Serial.print("[HTTP] GET...\n");
      // start connection and send HTTP header
      int httpCode = http.GET();

      // httpCode will be negative on error
      if (httpCode > 0) {
        // HTTP header has been send and Server response header has been handled
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        // file found at server
        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          Serial.println("done..");
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
    */
  }

  Serial.println(n);
  //Serial.println(vcc);


  delay(10000);
}
