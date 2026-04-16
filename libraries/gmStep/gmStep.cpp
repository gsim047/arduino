#include <gmStep.h>



int gmStep::set(int newval)
{
	if ( step < 1 )
		step = 1;
	if ( mode ){  // mode == 1
		int delta = newval - val;
		if ( delta < 0 )
			delta = -delta;
		if ( delta >= step ){
			val = newval;
			ch = 1;
		}else{
			ch = 0;
		}
	}else{        // mode == 0
		int sval = val / step;
		int snval = newval / step;
		if ( sval != snval ){
			val = newval;
			ch = 1;
		}else{
			ch = 0;
		}
	}
	return val;
}// gmStep::newval


void gmStep::init(const String &ini)
{
	int pos = ini.indexOf(",");
	if ( pos >= 0 ){
		String s1 = ini.substring(0, pos);
		String s2 = ini.substring(pos+1);
		if ( s1 != "" )
			step = s1.toInt();
		if ( s2 != "" )
			mode = s2.toInt();
	}else{
		if ( ini != "" ){
			step = ini.toInt();
		}
	}
	if ( step < 1 )
		step = 1;
	if ( mode != 0 && mode != 1 )
		mode = 1;
}// gmStep::init
