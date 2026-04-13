#include <OneWire.h>
#include <DallasTemperature.h>

#include <gmFn.h>
#include <gmUrl.h>


int pin = 2; // GPIO2 / D4
 
OneWire oneWire(pin);
DallasTemperature ds(&oneWire);

gmUrl url("http://192.168.1.201/esp/tmp/set.php")


int toDelay = 60000;
String name = "";


void setup() 
{
	//Serial.begin(115200);
	Serial_init();
	ds.begin();

	Serial.print("Found ");
	Serial.print(ds.getDeviceCount(), DEC);
	Serial.println(" device(s).");

	url.WiFi_connect();

	for ( int i = 0; i < 16; i++ ){
		if ( url.WiFi_check() )
			break;
		delay(250);
	}

   	url.clear();
   	url.set("event", "init");
	String res;
	int code = url.call(res);  //
	if ( code == 0 ){
		String bd = url.extract(res, "<pre>", "</pre>");
		gmCfgRead rd(bd);
		rd.get("name", name);
		rd.get("delay", toDelay);
	}
}// setup


void loop() 
{
	ds.requestTemperatures();
	int t = ds.getTempCByIndex(0);
 
	Serial.printf("%d°C\n", t);
	//Serial.println( "°C");

   	url.clear();
   	url.set("t", t);
    url.set("name", name);

	String res;
	int code = url.call(res);  //
	if ( code == 0 ){
		String bd = url.extract(res, "<pre>", "</pre>");
		gmCfgRead rd(bd);
		rd.get("name", name);
		rd.get("delay", toDelay);
	}
 
	delay(toDelay);
}// loop


/*
//#define ONE_WIRE_BUS 5 // вывод, к которому подключён DS18B20
#define TEMPERATURE_PRECISION 12 // точность измерений (9 ... 12)

OneWire oneWire(5); //ONE_WIRE_BUS);
DallasTemperature ds(&oneWire);
DeviceAddress Thermometer;
DeviceAddress insideThermometer;
 
float temp = 0.0; // текущее значение температуры
float min_temp = 100.0; // минимальное значение температуры
float max_temp = 0.0; // максимальное значение температуры


void setup() 
{
  Serial.begin(115200);
  //pinMode(5, INPUT);
  
  // put your setup code here, to run once:

  ds.begin(); // инициализация DS18B20
  //ds.getAddress(Thermometer, 0); // адрес DS18B20 (поиск по индексу)
  //ds.setResolution(Thermometer, TEMPERATURE_PRECISION);// установка точности измерения 9...12 разрядов

  Serial.println("\nStart!");
  
  Serial.print("Locating devices...");
//  ds.begin();
  Serial.print("Found ");
  Serial.print(ds.getDeviceCount(), DEC);
  Serial.println(" devices.");
}

void loop() {
  // put your main code here, to run repeatedly:

  ds.requestTemperatures(); // считывание значение температуры
  delay(1500);

  //temp = sensor.getTempC(Thermometer); // температура в градусах Цельсия
 
  //if (temp > max_temp) max_temp = temp; // обновление минимального значения температуры
  //if (temp < min_temp) min_temp = temp; // обновление максимального значения температуры

  //Serial.println(temp);
  
  Serial.println(ds.getTempCByIndex(0));

  delay(3000);
}

*/