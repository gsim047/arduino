#ifndef __lib_blink_h
#define __lib_blink_h 1



extern int ledx_HIGH; // = HIGH;
extern int ledx_LOW;  // = LOW;

extern int ledx_N; // = 2;
extern int ledx_Inv; // = 1;

// BUILTIN: 2/1
// D0: 16/0
// D1: 5/0
// D2: 4/0
// D5: 14/0
// D6: 12/0
// D7: 13/0


void ledx_init();
void ledx_initN(int N, int Inv);

void ledx_blink(int del);



#endif // __lib_blink_h
