#include <detpic32.h>

void delay(unsigned int ms) {
for( ; ms > 0; ms--) {
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}

int main(void)
{

TRISE = TRISE & 0xFFC0;
TRISB = TRISB | 0x0004;
int shift = 0;

int freq;

while (1) {

for (shift = 0; shift < 6; ++shift) 
	{

	if (PORTBbits.RB3) 
	{
	freq = 143;
	}

	else if (!PORTBbits.RB3)
	{
	freq = 333;
	}
	
	LATE = (LATE & 0xFFC0) | 0x1 << shift;
	delay(freq);
	}
}
return 0;
}



// 1/3 = 0.333
// 1/5 = 0.2
// 1/7 = 0.143
// 1/10 = 0.1
// 1/50 = 0.020
