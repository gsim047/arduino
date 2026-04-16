#include <Arduino.h>
#include <gmBlink.h>
#include <gmUrlS.h>
#include <gmCfgRead.h>
#include <gmStatus.h>
#include <gmFn.h>

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

int toDelay = 10000;


bool exec(const String &txt)
{
	if ( !url.WiFi_check() )
		return false;

	url.clear();
	url.set("txt", txt);
	n++;

	int code = url.call();  //
	if ( code ){
		gmCfgRead rd(url);
		rd.get("delay", toDelay);
	}
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

	url.fp = fingerprint_gsim047_ru;
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
