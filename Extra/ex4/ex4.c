#include <detpic32.h>

void delay(unsigned int ms)
{
for ( ; ms > 0; ms--) {
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}

void send2displays (unsigned char value){
    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
    static char displayFlag = 0;
    unsigned char dl = value & 0x0F;
    unsigned char dh = value >> 4;

    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dl]<<8);
    }
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (disp7Scodes[dh]<<8);
    }
    displayFlag = !displayFlag;
}

int main(void)
{
  TRISB = TRISB & 0x80FF; 			// configure RB8-RB14 as outputs
  TRISD = TRISD & 0xFF9F;			// configure RD5-RD6 as outputs
  LATD = (LATD & 0xFF9F) | 0x20;		// sets RD6 and RD5 to 0 and then sets RD6 to 1
  TRISE = TRISE & 0xFFF0;
  
	while(1)
	{
	
	switch(getChar())
	{
	case('0'):
	LATE = (LATE & 0xFFF0) | 0x1;
	// LATB = (LATB & 0x80FF) | disp7Scodes[0] << 8;
	send2displays(0);
	break;
	
	case('1'):
	LATE = (LATE & 0xFFF0) | 0x2;
	// LATB = (LATB & 0x80FF) | disp7Scodes[1] << 8;
	send2displays(1);
	break;
	
	case('2'):
	LATE = (LATE & 0xFFF0) | 0x4;
	// LATB = (LATB & 0x80FF) | disp7Scodes[2] << 8;
	send2displays(2);
	break;
	
	case('3'):
	LATE = (LATE & 0xFFF0) | 0x8;
	// LATB = (LATB & 0x80FF) | disp7Scodes[3] << 8;
	send2displays(3);
	break;
	
	default: 
	LATE = (LATE & 0xFFF0) | 0xF;
	// LATB = (LATB & 0x80FF) | disp7Scodes[15] << 8;
	send2displays(15);
	delay(1000);
	LATE = (LATE & 0xFFF0) | 0x0;
	LATB = (LATB & 0x80FF) | 0x0;
	break;
	}
}
  return 0;
}
