#include <Arduino.h>
#include <gmFn.h>
#include <gmUrl.h>
#include <gmCfgRead.h>
#include <gmBlink.h>
#include <gmStep.h>

// датчик освещённости

int dataPin = A0;

gmUrl url("http://192.168.1.201/esp/light/set.php");
gmBlink bl;

//ADC_MODE(ADC_VCC);

int toDelay = 10000;
String name;

int oldval = 0;
int n = 0;
//int step = 10;
gmStep st(10);


void setup()
{
	bl.blink(200);
	pinMode(dataPin, INPUT);
	Serial_init();
	bl.blink(500);

	n = 0;
	Serial.println("wifi...");
	url.WiFi_connect();
	bl.blink(500);
	Serial.println("wifi done!");
	int rs = url.WiFi_check();
	Serial.printf("check: %d\n", rs);

   	url.clear();
   	url.set("event", "init");
	int code = url.call();  //
	if ( code == 0 ){
		gmCfgRead rd(url);
		rd.get("name", url.name);
		String str;
		rd.get("step", str);
		if ( str != "" )
			st = gmStep(str);
	}
}// setup


void loop()
{
	if ( !url.WiFi_check() ){
		Serial.println("!WiFi check...");
		bl.blink(50);
		delay(2000);
		return;
	}

	n++;
	int val = analogRead(dataPin);

	st = val;
	if ( st.changed() ){
		url.clear();
	   	url.set("light", val);
		int code = url.call();  //
		if ( code == 0 ){
			gmCfgRead rd(url);
			String str;
			rd.get("step", str);
			if ( str != "" ){
				st = gmStep(str);
				st = val;
			}
		}

		Serial.printf("%d: %d\n", n, val);
	}
	/*
	int newval = val / step;
	if ( newval != oldval ){
		url.clear();
	   	url.set("light", val);
		int code = url.call();  //
		if ( code == 0 ){
			gmCfgRead rd(url);
			rd.get("step", step);
		}

		Serial.printf("%d: %d\n", n, val);
		oldval = newval;
	}*/

	delay(10);
}// loop

