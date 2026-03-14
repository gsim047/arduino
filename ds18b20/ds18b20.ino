#include <OneWire.h>
#include <DallasTemperature.h>
 
OneWire oneWire(2);
DallasTemperature ds(&oneWire);


void setup() 
{
	Serial.begin(115200);
	ds.begin();


	Serial.print("Found ");
	Serial.print(ds.getDeviceCount(), DEC);
	Serial.println(" devices.");
}

void loop() 
{
	ds.requestTemperatures();
	int t = ds.getTempCByIndex(0);
 
	Serial.print(t);
	Serial.println( "C");
 
	delay(10000);
}

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