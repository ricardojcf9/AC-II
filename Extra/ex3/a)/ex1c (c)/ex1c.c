#include <detpic32.h>

int main(void)
{
	TRISB = TRISB | 0x000F;		// configure RB3 - RB0 as outputs
	TRISE = TRISE & 0xFF00;		// configure RE3 - RE0 as inputs
	
 while (1) 
  {
	LATEbits.LATE0=PORTBbits.RB0;
	LATEbits.LATE1=PORTBbits.RB1;
	LATEbits.LATE2=PORTBbits.RB2;
	LATEbits.LATE3=PORTBbits.RB3;
	LATEbits.LATE4=PORTBbits.RB3;
	LATEbits.LATE5=PORTBbits.RB2;
	LATEbits.LATE6=PORTBbits.RB1;
	LATEbits.LATE7=PORTBbits.RB0;
 }
 return 0;
}
	
