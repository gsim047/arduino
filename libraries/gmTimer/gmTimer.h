#ifndef __gmTimer_h
#define __gmTimer_h 1

#include <Arduino.h>


class gmTimer {
public:
	gmTimer(int t) : tim(millis()), per(t) {}

	bool test();

public:
	mutable uint32_t tim;
	uint32_t per;
};// class gmTimer


#endif // __gmTimer_h
