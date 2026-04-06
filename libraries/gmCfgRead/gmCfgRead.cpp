#include "gmCfgRead.h"

/*
#include <algorithm>
#include <cctype>


static inline void ltrim(string &s) 
{
	s.erase(s.begin(), std::find_if_not(s.begin(), s.end(), [](unsigned char c){
		return std::isspace(c);
	}));
}//

static inline void rtrim(string &s) 
{
	s.erase(std::find_if_not(s.rbegin(), s.rend(), [](unsigned char c){
		return std::isspace(c);
	}).base(), s.end());
}//

static inline void trim(string &s) 
{
    rtrim(s);
    ltrim(s);
}//
*/


String gmCfgRead::read()
{
	String ret;
	int pos2 = data.indexOf("\n", pos);
	if ( pos2 >= 0 ){
		ret = data.substring(pos, pos2);
		int pos0 = pos;
		pos = pos2+1;
		//Serial.printf("pos0=%d pos2=%d pos=%d\n", pos0, pos2, pos);
	}else{
		ret = data.substring(pos);
		pos = data.length()+1;
	}
	return ret;
}// gmCfgRead::read


int gmCfgRead::get(std::map<String, String> &param)
{
//	int ret = 0;
	if ( vals.empty() ){
		while ( !eof() ){
			String key, val;

			String s = read();
			//Serial.println(String("read s:[") + s + "]");
			int pp0 = s.indexOf("#");
			if ( pp0 >= 0 ){
				s = s.substring(0, pp0);
			}
			s.trim();

			if ( s.length() == 0 )
				continue;

			int pp1 = s.indexOf("=");
			if ( pp1 > 0 ){
				key = s.substring(0, pp1);
				val = s.substring(pp1+1);
				//Serial.println(String("get key/value: [") + key + "]=[" + val + "]");
			}else{
				key = s.substring(0, pp1);
				val = "1";
			}
			vals[key] = val;
			//ret++;
		}
	}
	param = vals;
	return vals.size();
}// gmCfgRead::get


int gmCfgRead::get(const String &key, String &val)
{
	int ret = 0;
	std::map<String, String> param;
	get(param);
	std::map<String, String>::const_iterator it = param.find(key);
	if ( it != param.end() ){
		val = it->second;
		ret = 1;
	}
	return ret;
}// gmCfgRead::get


int gmCfgRead::get(const String &key, int &val)
{
	int ret = 0;
	String v;
	int res = get(key, v);
	if ( res ){
		val = v.toInt();
		ret = 1;
	}
	return ret;
}// gmCfgRead::get

