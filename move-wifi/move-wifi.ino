/*  
  *  Использование датчика движения типа PIR с платой Arduino.
  *  Более подробно о проекте на:  randomnerdtutorials.com/pirsensor
  *  Модифицирован Руи Сантосом (Rui Santos) на основе скетча Лимор Фрид (Limor Fried)
  *  Модифицирован Георгий Степанов (Georgiy Stepanov / gsim047)
*/

#include "gmUrl.h"
 
int led = 0;                 // контакт для светодиода
int sensor = 4;              // контакт для датчика
int state = LOW;             // по умолчанию никакого движения не определено

gmUrl url("http://192.168.1.201/esp/move.php");



void setup() 
{
	pinMode(led, OUTPUT);      // контакт для светодиода 
	pinMode(sensor, INPUT);    // контакт для датчика 
	Serial.begin(115200);      // инициализируем последовательную коммуникацию
	digitalWrite(led, LOW);

	url.WiFi_connect();
}// setup


void loop()
{
	int val = digitalRead(sensor);     // считываем данные от датчика
	
	if ( val != state ){
		if ( val == HIGH ){
			Serial.println("Motion detected!");  //  "Замечено движение!"
		}else{
			Serial.println("Motion stopped!"); //  "Движение прекращено!"
		}
	}

	if ( val == HIGH ){
		digitalWrite(led, HIGH);   // включаем светодиод
		delay(100);

		digitalWrite(led, LOW);    // выключаем светодиод
		delay(400);
	}else{
		digitalWrite(led, LOW);    // выключаем светодиод
	}
	delay(100);
	state = val;
}// loop
