#include <gmFn.h>


void Serial_init(int baud)  // def 115200
{
	Serial.begin(baud);
	Serial.printf("\n\n\n");
	for ( int t = 4; t > 0; t-- ){
		Serial.printf("[SETUP] WAIT %d...\n", t);
		Serial.flush();
		delay(1000);
	}
}// Serial_init


