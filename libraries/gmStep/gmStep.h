#ifndef __gmStep_h
#define __gmStep_h 1

#include <Arduino.h>



class gmStep {
public:
	gmStep(int Step) : val(-1), step(Step), mode(1), ch(0) {}
	gmStep(const String &ini) : val(-1), step(1), mode(1), ch(0) { init(ini); }
	gmStep(const gmStep &src) : val(src.val), step(src.step), mode(src.mode), ch(0) {}

	gmStep &operator=(const gmStep &src){
		if ( this != &src ){
			val = src.val; step = src.step; mode = src.mode; ch = 0;
		}
		return *this;
	}

	int changed() const { return ch; }

	int operator=(int newval){ return set(newval); }

private:
	int set(int newval);
	void init(const String &ini);

public:
	int val;
	int step;
	int mode;  // 0 - step from 0, 1 - from current val
	int ch;
};// class gmStep


#endif // __gmStep_h