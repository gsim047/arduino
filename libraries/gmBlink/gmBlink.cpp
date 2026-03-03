#include <gmBlink.h>
#include <Arduino.h>



// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


int gmBlink::defN(const char *Pin)
{
	String pin(Pin);
	if ( pin == "D0" )
		return 16;
	if ( pin == "D1" )
		return 5;
	if ( pin == "D2" )
		return 4;
	if ( pin == "D5" )
		return 14;
	if ( pin == "D6" )
		return 12;
	if ( pin == "D7" )
		return 13;
	return 2;
}// gmBlink::defN


bool gmBlink::defInv(int N)
{
	if ( N == 2 ) 
		return true;
	return false;
}// gmBlink::defInv


void gmBlink::blink(int tim) const
{
	if ( !ni ){
		pinMode(n, OUTPUT);
		ni = true;
	}
	int high = (inv ? LOW : HIGH);
	int low = (inv ? HIGH : LOW);
	digitalWrite(n, high);
	delay(tim);
	digitalWrite(n, low);
}// gmBlink::blink


void gmBlink::up() const
{
	if ( !ni ){
		pinMode(n, OUTPUT);
		ni = true;
	}
	int high = (inv ? LOW : HIGH);
	digitalWrite(n, high);
}// gmBlink::up


void gmBlink::down() const
{
	if ( !ni ){
		pinMode(n, OUTPUT);
		ni = true;
	}
	int low = (inv ? HIGH : LOW);
	digitalWrite(n, low);
}// gmBlink::down

