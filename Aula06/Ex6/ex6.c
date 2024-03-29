#include <detpic32.h>

void delay(int ms);
void send2displays(unsigned char value);

int main(void)
{
// Configure all (digital I/O, analog input, A/D module)

TRISBbits.TRISB4 = 1; 			// RBx digital output disconnected
AD1PCFGbits.PCFG4= 0; 			// RBx configured as analog input
AD1CON1bits.SSRC = 7; 			// Conversion trigger selection bits: in this
					// mode an internal counter ends sampling and
					// starts conversion
AD1CON1bits.CLRASAM = 1; 		// Stop conversions when the 1st A/D converter
					// interrupt is generated. At the same time,
					// hardware clears the ASAM bit
AD1CON3bits.SAMC = 16; 			// Sample time is 16 TAD (TAD = 100 ns)
AD1CON2bits.SMPI = 4-1; 		// Interrupt is generated after N samples
					// (replace N by the desired number of
					// consecutive samples)
AD1CHSbits.CH0SA = 4; 			// replace x by the desired input
					// analog channel (0 to 15)
AD1CON1bits.ON = 1; 			// Enable A/D converter
					// This must the last command of the A/D
					// configuration sequence

TRISB = TRISB & 0x80FF;			// Configure RB8 to RB14 as outputs
TRISD = TRISD & 0xFF9F;			// Configure RD5 to RB6 as outputs

while(1) 
	{
	int i = 0;
	int V = 0;		
	if(i == 0) 					// 0, 200ms, 400ms, 600ms, ...
	{
		AD1CON1bits.ASAM = 1;			// Start conversion
		while( IFS1bits.AD1IF == 0 ); 		// Wait while conversion not done (AD1IF == 0)
		int *p = (int *)(&ADC1BUF0);
		int sum = 0;
			for( i = 0; i < 4; i++ ) 
			{
			sum =+ p[i*4];			// Read conversion result (ADC1BUF0 value) and print it
			}
		sum = sum / 4;
		V = (sum * 33+511)/1023;
		IFS1bits.AD1IF = 0;			// Reset AD1IF
	}
	send2displays(V);
	delay(10);
	i = (i + 1) % 20; // 10*20 = 200 ms period
}
return 0;
}

void delay(int ms) 
{
	for (; ms > 0; ms--) 
	{
	resetCoreTimer();
	while(readCoreTimer() < 20000);
	}
}

void send2displays(unsigned char value){
    static const char disp7Scodes[] = { 0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71 };
    static char displayFlag = 0;    // static variable: doesn't loose its value between calls to function

    unsigned char digit_low = value & 0x0F;
    unsigned char digit_high = value >> 4;
    // if "displayFlag" is 0 then send digit_low to display_low
    if(displayFlag == 0){
        LATDbits.LATD5 = 1;
        LATDbits.LATD6 = 0;
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_low] << 8);
    }
    // else send digit_high to display_high
    else{
        LATDbits.LATD5 = 0;
        LATDbits.LATD6 = 1;
        LATB = (LATB & 0x80FF) | (disp7Scodes[digit_high] << 8);
    }
    // toggle "displayFlag" variable
    displayFlag = !displayFlag;
}
