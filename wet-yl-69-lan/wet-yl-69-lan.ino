#include <Arduino.h>
#include <gmFn.h>
#include <gmUrl.h>
#include <gmCfgRead.h>

// датчик влажности YL-69 (FC-28)

int dataPin = A0;

gmUrl url("http://192.168.1.201/esp/wet/set.php");

//ADC_MODE(ADC_VCC);

int n = 0;
int toDelay = 10000;
String name;



void setup()
{
	pinMode(dataPin, INPUT);
	Serial_init();

	n = 0;
	Serial.println("wifi...");
	url.WiFi_connect();
	Serial.println("wifi done!");
	int rs = url.WiFi_check();
	Serial.printf("check: %d\n", rs);

}// setup


void loop()
{
	if ( !url.WiFi_check() ){
		Serial.println("!WiFi check...");
		delay(2000);
		return;
	}

	int sensorValue = analogRead(dataPin);
	Serial.printf("%d: %d\n", n, sensorValue);

	url.clear();
	if ( n == 0 ){
		url.set("event", "init");
	}
	url.set("wet", sensorValue);
	url.set("name", name);

	String res;
	int code = url.call(res);  //
	//Serial.println(res);
	String bd = gmUrl::extract(res, "<pre>", "</pre>");
	//Serial.println(bd);

	gmCfgRead rd(bd);
	rd.get("delay", toDelay);
	rd.get("name", name);

	n++;
	delay(toDelay);
}// loop

