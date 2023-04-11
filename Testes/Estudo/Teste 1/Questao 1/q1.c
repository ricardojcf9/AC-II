#include <detpic32.h>

void delay(unsigned int ms) 
{
for ( ; ms > 0; ms--) {
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}

int main(void) 
{


TRISB = TRISB | 0x0005;
TRISE = TRISE & 0xFF03;
int freq;

while(1) {

	if (PORTBbits.RB2 && PORTBbits.RB0) 
	{
	freq = 95;
	}
	else if (!PORTBbits.RB2 && !PORTBbits.RB0) 
	{
	freq = 285;
	}
	else 
	{
	freq = 95;
	}

	LATE = (LATE & 0xFF03) | 0xC0;
	delay(freq);
	LATE = (LATE & 0xFF03) | 0x60;
	delay(freq);
	LATE = (LATE & 0xFF03) | 0x30;
	delay(freq);
	LATE = (LATE & 0xFF03) | 0x18;
	delay(freq);
	LATE = (LATE & 0xFF03) | 0x0C;
	delay(freq);
}
}

// 1/3.5  = 0.285
// 1/3    = 0.33
// 1/10.5 = 0.095
// 1/10   = 0.10
// 1/25   = 0.04
// 1/50   = 0.02
