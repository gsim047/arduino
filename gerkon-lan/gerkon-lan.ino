#include <Arduino.h>
#include <gmBlink.h>
#include <gmUrl.h>
#include <gmCfgRead.h>
#include <gmStatus.h>
#include <gmFn.h>

//#include "gsim047_ru.h"

// геркон:
//  нога 1 - на GND
//  нога 2 - на D2

const int pin = 4; // GPIO4 - это пин D2 на Wemos D1 Mini/NodeMCU
//static int state = LOW;
static gmStatus st(LOW, 6);  // 6*50 ms -> 300 ms
int n;

gmBlink bl;
gmUrl url("http://192.168.1.201/esp/set.php");


int toDelay = 10000;
String name = "";


bool exec(const String &txt)
{
	if ( !url.WiFi_check() )
		return false;

   	url.clear();
	String mac = url.WiFi_macAddress();
   	url.set("mac", mac);
   	url.set("txt", txt);
    if ( name.length() > 0 ){
    	url.set("name", name);
    }
   	n++;

   	String res;
   	int code = url.call(res);  //
   	//Serial.println(res);
   	String bd = url.extract(res, "<pre>", "</pre>");
//   	Serial.println(bd);

   	gmCfgRead rd(bd);
    rd.get("delay", toDelay);
    /*
   	std::map<String, String> par;
   	int nn = rd.get(par);
   	//Serial.printf("nn=%d\n", nn);
   	if ( nn > 0 ){
   		String dl = par["delay"];
   		if ( dl.length() > 0 ){
   			toDelay = dl.toInt();
//   			Serial.printf("param delay: %d\n", toDelay);
   		}
        String nm = par["name"];
        if ( nm.length() > 0 ){
        	name = nm;
        }
   	}*/
    return true;
}// exec


void show()
{
	if ( st == LOW ){
		Serial.println("closed (magnet is near)");
		exec("close");
		bl.down();
	}else{
		Serial.println("open (magnet is far)");
		exec("open");
		bl.up();
	}
}// show


void setup() 
{
	// Используем встроенный резистор подтяжки к 3.3V
	pinMode(pin, INPUT_PULLUP);
	bl.blink(200);
	n = 0;

	Serial_init();
	bl.blink(500);

	//url.fp = fingerprint_gsim047_ru;
	url.WiFi_connect();

	st = digitalRead(pin);
	show();

}// setup


void loop() 
{
	st = digitalRead(pin);
	if ( st.changed() ){
		show();
	}

	delay(50);
}// loop
