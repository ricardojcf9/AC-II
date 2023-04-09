#include <detpic32.h>

int main(void)
{
	TRISB = TRISB | 0x000F;		// configure RB3 - RB0 as outputs
	TRISE = TRISE & 0xFFF0;		// configure RE3 - RE0 as inputs
	
 while (1) 
  {
	(PORTB | 0x000F)  = (LATE & 0xFFF0) | 0x1;
	(PORTB | 0x000F) = (LATE & 0xFFF0) | 0x2;
	(PORTB | 0x000F) = (LATE & 0xFFF0) | 0x4;
	(PORTB | 0x000F) = (LATE & 0xFFF0) | 0x8;
 }
 return 0;
}
