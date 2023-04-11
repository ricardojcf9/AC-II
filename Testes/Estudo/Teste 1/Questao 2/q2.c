#include <detpic32.h>

void send2display(unsigned char value, int more) {
    static const char symbols[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x07F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };

    static char digit;

    if(!more) {
        //digit = value >> 4;
        LATD = (LATD & 0xFF9F) | 0x0040;

    } else {
        LATD = (LATD & 0xFF9F) | 0x0020;
        //digit = value & 0x0F;
    }

    digit = symbols[value];

    LATB = (LATB & 0x80FF) | (digit << 8);


}

void delay(unsigned int ms) {
    resetCoreTimer();
    while(readCoreTimer() < ms * 20000);
}

int main(void) 
{

TRISBbits.TRISB4 = 1;		// RBx digital output disconnected
AD1PCFGbits.PCFG4= 0;		// RBx configured as analog input
AD1CON1bits.SSRC = 7;		// Conversion trigger selection bits: in this
				// mode an internal counter ends sampling and
				// starts conversion
AD1CON1bits.CLRASAM = 1; 	// Stop conversions when the 1st A/D converter
				// interrupt is generated. At the same time,
				// hardware clears the ASAM bit
AD1CON3bits.SAMC = 16;		// Sample time is 16 TAD (TAD = 100 ns)
AD1CON2bits.SMPI = 4-1; 	// Interrupt is generated after N samples
				// (replace N by the desired number of
				// consecutive samples)
AD1CHSbits.CH0SA = 4;		// replace x by the desired input
				// analog channel (0 to 15)
AD1CON1bits.ON = 1;		// Enable A/D converter
				// This must the last command of the A/D
				// configuration sequence
				
int sum = 0;
int avg;
int i;
int scaled;
	
TRISB = TRISB & 0x80FF ;	// output RB14 - RB8

TRISD = TRISD & 0xFF9F; 	// output RD6 - RD5

TRISBbits.TRISB3 = 1;   	// input RB3

TRISE = TRISE & 0xFFBD;		// output RE6 and RE1

while(1) 
{

AD1CON1bits.ASAM = 1;
while (IFS1bits.AD1IF == 0 );

int *p = (int *) (&ADC1BUF0);
for(i = 0; i < 4; i++) 
{
sum = sum + *p;
p = p + 4;
}

IFS1bits.AD1IF = 0;

avg = sum / 4;

printInt(avg, 2 | 12 << 16);

putChar('\r');

scaled = (avg * 10 / 1023) + 4;

send2display(scaled, PORTBbits.RB3);

LATE = LATE ^ 0x0042;

delay(250);
}

return 0;
}
