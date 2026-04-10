#include "gmStat.h"


void gmStat::init()
{
	nn.clear();
	for ( int i = nMin; i < nMax; i += nN ){
		nn[i] = 0;
	}
}// gmStat::init


int gmStat::set(int val)
{
	int ret = 0;
	if ( val >= nMin && val < nMax ){
		int a = (val - nMin) / nN;
		int b = nMin + a * nN;
		nn[b] += 1;
		ret = nn[b];
	}
	return ret;
}// gmStat::set


int gmStat::middle() const
{
	int ret = 0;
	int sum = 0;
	int n = 0;
	for ( std::map<int, int>::const_iterator it = nn.begin(); it != nn.end(); ++it ){
		n += it->second;
		sum += it->first * it->second;
	}
	if ( n ){
		ret = sum / n;
	}
	return ret;
}// gmStat::middle


int gmStat::size() const
{
	int ret = 0;
	for ( std::map<int, int>::const_iterator it = nn.begin(); it != nn.end(); ++it ){
		ret += it->second;
	}
	return ret;
}// gmStat::size

