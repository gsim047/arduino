// PIR HC-SR501
// https://voltiq.ru/arduino-and-sensor-hc-sr501/

//#include <gmBlink.h>
#include <gmUrl.h>
#include <gmFn.h>
#include <gmCfgRead.h>
 
//int led = 0;                   // контакт для светодиода / 
int sensor = 2;                // контакт для датчика    / D4
int state = LOW;               // по умолчанию никакого движения не определено

int n = 0;
//gmBlink ld(led);
gmUrl url("http://192.168.1.201/esp/move/set.php");


void setup() 
{
	//pinMode(led, OUTPUT);      // контакт для светодиода 
	pinMode(sensor, INPUT);    // контакт для датчика 
	//Serial.begin(115200);      // инициализируем последовательную коммуникацию
	//digitalWrite(led, LOW);

//	ld.down();

	Serial_init();

	url.WiFi_connect();

	for ( int i = 0; i < 16; i++ ){
		Serial.printf("[WIFI] WAIT %d\n", i+1);
		if ( url.WiFi_check() )
			break;
		delay(200);
	}
	Serial.println(url.WiFi_macAddress());

   	url.clear();
   	url.set("event", "init");
//	String res;
	int code = url.call();  //
	if ( code == 0 ){
		//String bd = url.extract(res, "<pre>", "</pre>");
		gmCfgRead rd(url);
		//rd.get("name", name);
	}
}// setup



bool exec(const String &txt)
{
	if ( !url.WiFi_check() )
		return false;

   	url.clear();
//	String mac = url.WiFi_macAddress();
//   	url.set("mac", mac);
	//url.set("name", name);
   	url.set("event", txt);
   	n++;

	//String res;
	Serial.println(url.get());
	int code = url.call();  //
	//Serial.printf("code: %d\n", code);
	if ( code != 0 )
		return false;
    
	//String bd = url.extract(res, "<pre>", "</pre>");
	//Serial.println(bd);

	gmCfgRead rd(url);
	//Serial.println("to get [name]");
	//rd.get("name", name);
	//Serial.printf("name is [%s]\n", name.c_str());
    return true;
}// exec


void loop()
{
	n++;
	int val = digitalRead(sensor);     // считываем данные от датчика
//	Serial.printf("val: %d\n", val);
	
	if ( val != state ){
		String msg;
		if ( val == HIGH ){
			msg = "MotionAlarm";
		}else{
			msg = "MotionStop";
		}
		Serial.printf("%d %s\n", n, msg.c_str());
		int res = exec(msg);
	}

	/*
	if ( val == HIGH ){
		ld.up();
		//delay(100);

		//ld.down();
		//delay(400);
	}else{
		ld.down();
	}*/
	delay(100);
	state = val;
	//Serial.printf("n=%d state=%d val=%d\n", n, state, val);
}// loop
