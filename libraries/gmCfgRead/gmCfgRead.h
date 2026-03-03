#ifndef __gmCfgRead_h
#define __gmCfgRead_h 1

#include <Arduino.h>
//#include <string>
//using std::string;
#include <map>


class gmCfgRead {
public:
	gmCfgRead() : pos(0) {}
	gmCfgRead(const gmCfgRead &src) : data(src.data), pos(src.pos) {}
	gmCfgRead(const String &s) : data(s), pos(0) {}

	gmCfgRead &operator=(const gmCfgRead &src){
		if ( &src != this ){
			data = src.data; pos = src.pos;
		}
		return *this;
	}

	gmCfgRead &operator=(const String &src){
		data = src; pos = 0;
		return *this;
	}

	void clear(){ pos = 0; }

	bool eof() const {
		return pos >= data.length();
	}
	int size() const {
		return data.length();
	}

	String read();

	int get(std::map<String, String> &param);

public:
	String data;
	int pos;
};// class gmCfgRead



#endif // __gmCfgRead_h
