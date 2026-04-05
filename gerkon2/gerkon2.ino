#include <Arduino.h>
#include <gmStatus.h>
#include <gmFn.h>
#include <gmBlink.h>

// геркон:
//  нога 1 - на GND
//  нога 2 - на D2
//  нога 2 - через резистор 10 кОм на 5В

const int pin = 4; // GPIO4 - это пин D2 на Wemos D1 Mini/NodeMCU
//static int state = LOW;
static gmStatus st(LOW, 5);
gmBlink bl;        // BUILDIN - 


void setup() 
{
	//Serial.begin(115200);
	// Используем встроенный резистор подтяжки к 3.3V
	pinMode(pin, INPUT_PULLUP);
	bl.down();
	Serial_init();
}// setup


void loop() 
{
	st = digitalRead(pin);
	if ( st.changed() ){
		int s = st;
		if ( st ){
			Serial.println("open (magnet is far)");
			bl.down();
		}else{
			Serial.println("closed (magnet is near)");
			bl.up();
		}
	}

	/*
	if ( state != rdState ){
		if ( rdState == LOW ){
			Serial.println("closed (magnet is near)");
		}else{
			Serial.println("open (magnet is far)");
		}
		state = rdState;
	}*/
	delay(50);
}// loop
