#ifndef __gmStatus_h
#define __gmStatus_h 1

#include <Arduino.h>


class gmStatus {
public:
	gmStatus(int S = LOW, int Cnt = 5) : st(S), lst(S), mcnt(Cnt), ccnt(0), chgt(0) {}
	gmStatus(const gmStatus &src) : st(src.st), lst(src.st), mcnt(src.mcnt), ccnt(0), chgt(0) {}

	gmStatus &operator=(const gmStatus &src){
		if ( this != &src ){
			st = src.st; lst = st; mcnt = src.mcnt; ccnt = 0; chgt = 0;
		}
		return *his;
	}

	operator int() const { return st; }

	int operator=(int val){
		chgt = 0;
		if ( val != st ){
			if ( val == lst ){
				ccnt--;
				if ( ccnt <= 0 ){
					st = val;
					chgt = 1;
				}
			}else{
				ccnt = mcnt;
			}
		}
		lst = val;
		return val;
	}

	bool changed() const { return chgt; }
	bool set(int val){
		operator=(val);
		return changed();
	}

public:
	int st;           // status
	int lst;          // last val
	int ccnt;         // cur count
	int mcnt;         // max count
	int chgt;         // just changed
};// class gmStatus	


#endif // __gmStatus_h
