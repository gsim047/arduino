#include <gmBlink.h>
#include <Arduino.h>



bool gmBlink::defInv(int N)
{
	if ( N == 2 ) 
		return true;
	return false;
}// gmBlink::defInv


void gmBlink::bl(int tim) const
{
	if ( !ni ){
		pinMode(n, OUTPUT);
		ni = true;
	}
	int high = (inv ? LOW : HIGH);
	int low = (inv ? HIGH : LOW);
	digitalWrite(n, high);
	delay(tim);
	digitalWrite(n, low);    // turn the LED off by making the voltage LOW
}//

