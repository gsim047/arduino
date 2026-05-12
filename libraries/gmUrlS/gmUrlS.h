#ifndef __gmUrlS_h
#define __gmUrlS_h 1

#include <Arduino.h>
#include <gmUrl.h>




class gmUrlS : public gmUrl {
public:
	gmUrlS(const String &Url0) : 
		gmUrl(Url0), fp(NULL) { slice(Url0, prot, url0, url1, port); };
//	gmUrlS(const String &Url0, const String &Url1, int Port = 443) : url0(Url0), url1(Url1), port(Port), fp(NULL) {};
	gmUrlS(const gmUrlS &src) : 
		gmUrl(src), prot(src.prot), fp(src.fp), param(src.param), dbg(src.dbg) {}

	gmUrlS &operator=(const gmUrlS &src){
		if ( &src != this ){
			prot = src.prot; url0 = src.url0; url1 = src.url1; port = src.port; fp = src.fp; param = src.param; dbg = src.dbg;
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
	static String extract(const String &res, const String &s1, const String &s2);

	static void WiFi_connect();
	static bool WiFi_check();
	static String WiFi_macAddress();

	bool slice(const String &url, String &pr, String &u1, String &u2, int &prt);

public:
	String prot;  // http:// or https://
	String url0;  // https://server.ru or http://192.168.1.10
	String url1;  // /data/set.php
	int port;
	const char* fp;
	String param;
	int dbg;
	String name;
	String res;
};// class gmUrl



#endif // __gmUrlS_h
