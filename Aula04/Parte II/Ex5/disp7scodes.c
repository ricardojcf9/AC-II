#include <detpic32.h>

void delay(int unsigned ms)
{
for ( ; ms > 0; ms--) 
	{
resetCoreTimer();
while (readCoreTimer() < 20000);
	}
}

int main(void)
{
static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};

TRISB = TRISB & 0x80FF;			// configure RB8-RB14 as outputs
TRISD = TRISD & 0xFF9F;			// configure RD5-RD6 as outputs
LATD = (LATD & 0xFF9F) | 0x20;		// sets RD6 and RD5 to 0 and then sets RD6 to 1

while(1)
{
int i = 0;
for (; i <= 15; i++) 
{
	int code = disp7Scodes[i];	
	LATB = (LATB & 0x80FF) | code << 8;
	delay(500);	
}
}
return 0;
}
