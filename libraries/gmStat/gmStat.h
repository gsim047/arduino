#ifndef __gmStat_h
#define __gmStat_h 1

#include <Arduino.h>
#include <map>



class gmStat {
public:
	gmStat(int nmin = 0, int nmax = 1000, int n = 10) : nMin(nmin), nMax(nmax), nN(n) { init(); }
	gmStat(const gmStat &src) : nMin(src.nMin), nMax(src.nMax), nN(src.nN), nn(src.nn) {}
	~gmStat() {};

	gmStat& operator=(const gmStat &src){
		if ( this != &src ){
			nMin = src.nMin; nMax = src.nMax; nN = src.nN; nn = src.nn;
		}
		return *this;
	}

	void clear() { nn.clear(); }
	int operator+=(int val) { return set(val); }

	int size() const;
	int middle() const;

private:
	void init();
	int set(int val);

public:
	int nMin;
	int nMax;
	int nN;
	std::map<int, int> nn;
};// class gmStat


#endif // __gmStat_h
