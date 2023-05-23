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
unsigned char segment;
TRISB = TRISB & 0x80FF;			// configure RB8-RB14 as outputs
TRISD = TRISD & 0xFF9F;			// configure RD5-RD6 as outputs
LATD = (LATD & 0xFF9F) | 0x40;		// sets RD6 and RD5 to 0 and then sets RD6 to 1

while(1)
{

LATD = LATD ^ 0x60;


segment = 1;
int i;
for(i=0; i < 7; i++)
{
LATB = (LATB & 0x80FF) | segment << 8;	// send "segment" value to display
delay(500);				// wait 0.5 second
segment = segment << 1;
}
}
return 0;
}
