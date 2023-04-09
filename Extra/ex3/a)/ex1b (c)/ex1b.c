#include <detpic32.h>

int main(void)
{
	TRISB = TRISB | 0x000F;		// configure RB3 - RB0 as outputs
	TRISE = TRISE & 0xFFF0;		// configure RE3 - RE0 as inputs
	
 while (1) 
  {
	LATEbits.LATE0=PORTBbits.RB3;
	LATEbits.LATE1=PORTBbits.RB2;
	LATEbits.LATE2=PORTBbits.RB1;
	LATEbits.LATE3=PORTBbits.RB0;
 }
 return 0;
}
	
	
