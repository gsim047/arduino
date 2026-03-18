#include <Arduino.h>
#include <gmBlink.h>
#include <gmUrlS.h>
#include <gmCfgRead.h>
#include <gmStatus.h>

#include "gsim047_ru.h"

// геркон:
//  нога 1 - на GND
//  нога 2 - на D2
//  нога 2 - через резистор 10 кОм на 5В  -- no need

const int pin = 4; // GPIO4 - это пин D2 на Wemos D1 Mini/NodeMCU
//static int state = LOW;
static gmStatus st(LOW, 6);  // 6*50 ms -> 300 ms
int n;

gmBlink bl;
gmUrlS url("https://gsim047.ru/esp/set.php");


void setup() 
{
	// Используем встроенный резистор подтяжки к 3.3V
	pinMode(pin, INPUT_PULLUP);
	bl.blink(200);
	n = 0;

	Serial.begin(115200);
	Serial.printf("\n\n\n");

	for ( int t = 4; t > 0; t-- ){
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}

	url.fp = fingerprint_gsim047_ru;
	url.WiFi_connect();
}// setup


int toDelay = 10000;

void exec(const String &txt)
{
	if ( !url.WiFi_check() )
		return;

   	url.clear();
	String mac = url.WiFi_macAddress();
   	url.set("mac", mac);
   	url.set("txt", txt);
   	n++;

   	String res;
   	int code = url.call(res);  //
   	//Serial.println(res);
   	String bd = url.extract(res, "<pre>", "</pre>");
   	Serial.println(bd);

   	gmCfgRead rd(bd);
   	std::map<String, String> par;
   	int nn = rd.get(par);
   	//Serial.printf("nn=%d\n", nn);
   	if ( nn > 0 ){
   		String dl = par["delay"];
   		if ( dl.length() > 0 ){
   			toDelay = dl.toInt();
   			Serial.printf("param delay: %d\n", toDelay);
   		}
   	}
}// exec


void loop() 
{
	st = digitalRead(pin);

	if ( st.changed() ){
		if ( st == LOW ){
			Serial.println("closed (magnet is near)");
			exec("close");
		}else{
			Serial.println("open (magnet is far)");
			exec("open");
		}
	}
	delay(50);
}// loop
