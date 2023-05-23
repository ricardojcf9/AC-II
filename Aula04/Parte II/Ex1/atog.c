#include <detpic32.h>

void delay(unsigned int ms)
{
for ( ; ms > 0; ms--) 
	{
resetCoreTimer();
while (readCoreTimer() < 20000);
	}
}

int main(void)
{

TRISB = TRISB && 0x00FF;
TRISD = TRISD & 0xFF87;
LATDbits.LATD5 = 1;
LATDbits.LATD6 = 0;
LATB = (LATB & 0x80FF);
 
while (1)
{
  switch (getChar())
  {
  case 'A':
  case 'a':
  	LATB = (LATB & 0x80FF) | 0x100;
  	break;
  case 'B':
  case 'b':
  	LATB = (LATB & 0x80FF) | 0x200;
  case 'C':
  case 'c':
  	LATB = (LATB & 0x80FF) | 0x400;
  case 'D':
  case 'd':
  	LATB = (LATB & 0x80FF) | 0x800;
  case 'E':
  case 'e':
  	LATB = (LATB & 0x80FF) | 0x1000;
  case 'F':
  case 'f':
  	LATB = (LATB & 0x80FF) | 0x2000;
  case 'G':
  case 'g':
  	LATB = (LATB & 0x80FF) | 0x4000;
  	
 }
 }
  	
  return 0;
 }
  

