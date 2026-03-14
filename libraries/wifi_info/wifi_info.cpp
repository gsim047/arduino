#include <wifi_info.h>


static char ssid1[32] = { "HomeAsus87U" };
static char psw1[32]  = { "atlana8312" };

static char ssid2[32] = { "HomeAsus_X" };
//char psw2[32]  = { "***" };

char *wifi_ssid = ssid2;
char *wifi_psw  = psw1;


void setWiFi(int n)
{
	switch ( n ){
	case 1:
		wifi_ssid = ssid1;
		wifi_psw  = psw1;
		break;
	default:
		wifi_ssid = ssid2;
		wifi_psw  = psw1;
		break;
	}
}// setWiFi