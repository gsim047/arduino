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
			data = src.data; pos = src.pos; vals.clear();
		}
		return *this;
	}

	gmCfgRead &operator=(const String &src){
		data = src; pos = 0; vals.clear();
		return *this;
	}

	void clear(){ pos = 0; vals.clear(); }

	bool eof() const {
		return pos >= data.length();
	}
	int size() const {
		return data.length();
	}

private:
	String read();

public:
	int get(std::map<String, String> &param);
	int get(const String &key, String &val);
	int get(const String &key, int &val);

public:
	String data;
	int pos;
	std::map<String, String> vals;
};// class gmCfgRead



#endif // __gmCfgRead_h
