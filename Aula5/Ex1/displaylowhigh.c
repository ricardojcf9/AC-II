#include <detpic32.h>

void delay(int unsigned ms)
{
for ( ; ms > 0; ms--) 
	{
resetCoreTimer();
while (readCoreTimer() < 20000);
	}
}

int main(void) {
{
TRISB = TRISB & 0x80FF;			// configure RB8-RB14 as outputs
TRISD = TRISD & 0xFF9F;			// configure RD5-RD6 as outputs
while(1)
{
send2displays(0x15);
delay(200);				// wait 0.2s
}

return 0;
}

void send2displays(unsigned char value)
{
static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
unsigned char dh = disp7Scodes[value >> 4];      // Get the value at 7..4
unsigned char dl = disp7Scodes[value & 0x0F];    // Get the value at 3..0
TRISB = TRISB & 0x80FF;			// configure RB8 to RB14 as outputs
TRISD = TRISD & 0xFF9F;			// configure RD5 to RD6 as outputs
LATD = (LATD & 0x0040) | 0xFFDF;	// select display high
LATB = (LATB &	0x80FF) | dh << 8;	// send digit_high (dh) to display:
delay (10);
LATD = (LATD & 0x0020) | 0xFFBF;	// select display low
LATB = (LATB &	0x80FF) | dl << 8;	// send digit_low (dl) to display:
}
}

