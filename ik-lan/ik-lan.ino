#include <Arduino.h>
#include <gmFn.h>
#include <gmUrl.h>
#include <gmCfgRead.h>
#include <gmBlink.h>
#include <gmStep.h>

// ик-датчик расстояния

int dataPin = A0;
int signalPin = D2;

gmUrl url("http://192.168.1.201/esp/ik/set.php");
gmBlink bl;

//ADC_MODE(ADC_VCC);

int toDelay = 10000;
String name;

int oldval = -1;
int oldsig = -1;
int n = 0;
//int step = 10;
gmStep st(10);


void setup()
{
	bl.blink(200);
	pinMode(dataPin, INPUT);
	pinMode(signalPin, INPUT);
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
		int s = 0;
		rd.get("step", s);
		if ( s > 0 && s != st.step )
			st.setStep(s);
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
	int sig = digitalRead(signalPin);

	st = val;
	if ( st.changed() ){
		url.clear();
	   	url.set("dist", val);
		int code = url.call();  //
		if ( code == 0 ){
			gmCfgRead rd(url);
			int s = 0;
			rd.get("step", s);
			if ( s > 0 && s != st.step ){
				st.setStep(s);
			}
		}

		Serial.printf("%d: %d\n", n, val);
	}

	delay(10);
}// loop

