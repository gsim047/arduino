#ifndef __gmBlink_h
#define __gmBlink_h 1


class gmBlink {
public:
	gmBlink() : n(2), inv(true), ni(false) {}
	gmBlink(int N) : n(N), inv(defInv(N)), ni(false) {}
	gmBlink(int N, bool Inv) : n(N), inv(Inv), ni(false) {}

	gmBlink &operator=(const gmBlink &src){
		if ( &src != this ){
			n = src.n;
			inv = src.inv;
			ni = false;
		}
		return *this;
	}

	static bool defInv(int N);

	void bl(int tim) const;

public:
	int n;
	bool inv;
	mutable bool ni; // inited
};// gmBlink


#endif // __gmBlink_h
