#include <detpic32.h>

void delay(int ms);

int main(void) {
	
	TRISEbits.TRISE0 = 0;
	LATEbits.LATE0 = 0;
	
	TRISBbits.TRISB8 = 1;
	
	while(1) {
	
	if (PORTBbits.RB0 == 1) {
	LATEbits.LATE0 = 1;
	delay(3000);
	}
	else 
	LATEbits.LATE0 = 0;
	}
	
}

void delay (int ms) 
{
for ( ; ms > 0; ms--) 
{
resetCoreTimer();
while(readCoreTimer() > 20000);
}
}
