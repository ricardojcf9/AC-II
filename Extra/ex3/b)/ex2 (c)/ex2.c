#include <detpic32.h>

void delay(unsigned int ms)
{
for ( ; ms > 0; ms--) {
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}

int main(void)
{
  TRISE = TRISE & 0xFFF0;
  
	while(1)
	{
	
	switch(getChar())
	{
	case('0'):
	LATE = (LATE & 0xFFF0) | 0x1;
	break;
	
	case('1'):
	LATE = (LATE & 0xFFF0) | 0x2;
	break;
	
	case('2'):
	LATE = (LATE & 0xFFF0) | 0x4;
	break;
	
	case('3'):
	LATE = (LATE & 0xFFF0) | 0x8;
	break;
	
	default: 
	LATE = (LATE & 0xFFF0) | 0xF;
	delay(1000);
	LATE = (LATE & 0xFFF0) | 0x0;
	break;
	}
}
  return 0;
}
