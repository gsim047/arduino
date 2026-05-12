#ifndef __gmUrl_h
#define __gmUrl_h 1

#include <Arduino.h>





class gmUrl {
public:
	gmUrl(const String &Url0) : 
		dbg(0) { String pr; slice(Url0, pr, url0, url1, port); };
	gmUrl(const gmUrl &src) : 
		url0(src.url0), url1(src.url1), port(src.port), param(src.param), dbg(src.dbg) {}

	gmUrl &operator=(const gmUrl &src){
		if ( &src != this ){
			url0 = src.url0; url1 = src.url1; port = src.port; param = src.param; dbg = src.dbg;
		}
		return *this;
	}

	void clear();
	void set(const String &key, const String &val);
	void set(const String &key, int val);
	void set(const String &key, float val);

	String get() const; // ret url
	//int call(String &res);      // ret errorcode & result of curl
	int call();                 // ret errorcode

	void init();
	static String extract(const String &res, const String &s1, const String &s2);

	static void WiFi_connect();
	static bool WiFi_check();
	static String WiFi_macAddress();

//	bool slice(const String &url, String &u1, String &u2, int &prt);
	bool slice(const String &url, String &pr, String &u1, String &u2, int &prt);

public:
	String url0;  // https://server.ru or http://192.168.1.10
	String url1;  // /data/set.php
	int port;
	const char* fp;
	String param;
	int dbg;
	String name;
	String res;
};// class gmUrl



#endif // __gmUrl_h
