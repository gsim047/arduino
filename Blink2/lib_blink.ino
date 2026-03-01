#include "lib_blink.h"


int ledx_HIGH = HIGH;
int ledx_LOW  = LOW;

int ledx_N = 2;
int ledx_Inv = 1;

// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


void ledx_init()
{
	if ( ledx_Inv ){
		ledx_HIGH = LOW;
		ledx_LOW  = HIGH;
	}
	pinMode(ledx_N, OUTPUT);
}// ledx_init


void ledx_initN(int N, int Inv)
{
	ledx_N = N;
	ledx_Inv = Inv;
	ledx_init();
}// ledx_initN


void ledx_blink(int del)
{
	digitalWrite(ledx_N, ledx_HIGH);
	delay(del);
	digitalWrite(ledx_N, ledx_LOW);
}// ledx_blink

