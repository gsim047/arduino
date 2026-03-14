#ifndef __gmUrl_h
#define __gmUrl_h 1

#include <Arduino.h>



void WiFi_connect();
bool WiFi_check();
String WiFi_macAddress();



class gmUrl {
public:
	gmUrl(const String &Url0) : url0(Url0) {};
	gmUrl(const gmUrl &src) : url0(src.url0), param(src.param) {}

	gmUrl &operator=(const gmUrl &src){
		if ( &src != this ){
			url0 = src.url0; param = src.param;
		}
		return *this;
	}

	void clear();
	void set(const String &key, const String &val);
	void set(const String &key, int val);
	void set(const String &key, float val);

	String get() const; // ret url
	int call(String &res);      // ret errorcode & result of curl
	int call();                 // ret errorcode
	static String extract(const String &res, const String &s1, const String &s2);


public:
	String url0;  // https://server.ru or http://192.168.1.10
//	String url1;  // /data/set.php
	String param;
};// class gmUrl



#endif // __gmUrl_h
