/*  
  *  Использование датчика движения типа PIR с платой Arduino.
  *  Более подробно о проекте на:  randomnerdtutorials.com/pirsensor
  *  Модифицирован Руи Сантосом (Rui Santos) на основе скетча Лимор Фрид (Limor Fried)
  *  Модифицирован Георгий Степанов (Georgiy Stepanov / gsim047)
*/

// PIR HC-SR501
// https://voltiq.ru/arduino-and-sensor-hc-sr501/

#include <gmBlink.h>


int led = 2;                   // контакт для светодиода
int sensor = 4;                // контакт для датчика
int state = LOW;               // по умолчанию никакого движения не определено

int n = 0;
gmBlink ld(led);


void setup() 
{
	pinMode(led, OUTPUT);      // контакт для светодиода 
	pinMode(sensor, INPUT);    // контакт для датчика 
	Serial.begin(115200);      // инициализируем последовательную коммуникацию
	//digitalWrite(led, LOW);
	ld.down();
	Serial.println("1");
	Serial.println("2");
	Serial.println("3");
	Serial.println("4");
}// setup


void loop()
{
	n++;
	int val = digitalRead(sensor);     // считываем данные от датчика
	
	if ( val != state ){
		if ( val == HIGH ){
			Serial.println("Motion detected!");  //  "Замечено движение!"
		}else{
			Serial.println("Motion stopped...");   //  "Движение прекращено!"
		}
	}

	if ( val == HIGH ){
		//digitalWrite(led, HIGH);   // включаем светодиод
		ld.up();
		delay(100);

		//digitalWrite(led, LOW);    // выключаем светодиод
		ld.down();
		delay(400);
	}else{
		//digitalWrite(led, LOW);    // выключаем светодиод
		ld.down();
	}
	delay(100);
	state = val;
	Serial.printf("n=%d state=%d val=%d\n", n, state, val);
}// loop
