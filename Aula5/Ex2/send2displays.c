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
TRISB = TRISB & 0x80FF;			// configure RB8-RB14 as outputs
TRISD = TRISD & 0xFF9F;			// configure RD5-RD6 as outputs
while(1)
{
send2displays(0x15);
delay(200);// wait 0.2s
}
}
