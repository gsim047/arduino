#ifndef __gmBlink_h
#define __gmBlink_h 1

// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


class gmBlink {
public:
	gmBlink() : n(2), inv(true), ni(false) {}
	gmBlink(int N) : n(N), inv(defInv(n)), ni(false) {}
	gmBlink(int N, bool Inv) : n(N), inv(Inv), ni(false) {}
	gmBlink(const char *pin) : n(defN(pin)), ni(false) {
		inv = defInv(n);
	}

	gmBlink &operator=(const gmBlink &src){
		if ( &src != this ){
			n = src.n;
			inv = src.inv;
			ni = false;
		}
		return *this;
	}

	static int defN(const char *pin);
	static bool defInv(int N);

	void bl(int tim) const;

public:
	int n;
	bool inv;
	mutable bool ni; // inited
};// gmBlink


#endif // __gmBlink_h
