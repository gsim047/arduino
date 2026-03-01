#include <gmUrl.h>


void gmUrl::set(const String &key, const String &val)
{
	if ( param.length() != 0 ){
		param += "&";
	}
	param += key;
	param += "=";
	param += val;
}// gmUrl::set


void gmUrl::set(const String &key, int val)
{
	set(key, String(val));
}// gmUrl::set


void gmUrl::set(const String &key, float val)
{
	set(key, String(val));
}// gmUrl::set


String gmUrl::get() const
{
	String ret = url0;
	if ( param.length() != 0 ){
		ret += "?";
		ret += param;
	}
	return ret;
}// gmUrl::get


void gmUrl::clear()
{
	param = "";
}
