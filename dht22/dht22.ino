
#include <Arduino.h>

#include <DHT_U.h>
#include <DHT.h>


#define SENSOR	A0
//#define DHTTYPE	DHT11
//#define DHTPIN 2

//DHT dht(DHTPIN, DHTTYPE);

ESP8266WiFiMulti WiFiMulti;
int n = 0;
char ssid[] = "HomeAsus_X";
char psw[] = "atlana8312";
char url0[] = "http://192.168.1.201";

//#define pinSDA 4
//#define pinSCL 5

//float P; // В данную переменную мы будем пересчитывать давление в милиметры ртутного столба
//Adafruit_BMP085_Unified bmp(10085);

ADC_MODE(ADC_VCC);



void WiFiConnect()
{
  if ( (WiFiMulti.run() == WL_CONNECTED) ) {
    return;
  }
  Serial.println("connecting...");
  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP(ssid, psw);
}//


void blink(int tim, int level1, int level0)
{
  digitalWrite(LED_BUILTIN, level1);   // turn the LED on (HIGH is the voltage level)
  delay(tim);                       // wait for a second
  digitalWrite(LED_BUILTIN, level0);    // turn the LED off by making the voltage LOW
  
}//


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
    	int vcc = ESP.getVcc();
    	sprintf(url, "%s/esp/set1.php?dat=t-%d", url0, vcc);
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


  delay(5000);
}
