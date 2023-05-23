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
LATDbits.LATD5 = 0; 			// enable display low (RD5)
LATDbits.LATD6 = 1;			// disable display high (RD6)
TRISB = TRISB & 0x80FF;			// configure RB8-RB14 as outputs
TRISB = TRISB & 0xFF9F;			// configure RD5-RD6 as outputs

while(1)
{
segment = 1;
int i;
for(i=0; i < 7; i++)
{
LATB = (LATB & 0x80FF) | segment << 8;	// send "segment" value to display
delay(500);				// wait 0.5 second
segment = segment << 1;
}
LATDbits.LATD5 = !LATDbits.LATD5;
LATDbits.LATD6 = !LATDbits.LATD6;	// toggle display selection
}
return 0;
}
