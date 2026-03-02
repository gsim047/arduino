#include <gmTimer.h>


bool gmTimer::test()
{
	uint32_t delta = millis() - tim;
	if ( delta >= per ){
		tim = millis();
		return true;
	}
	return false;
}// gmTimer::test