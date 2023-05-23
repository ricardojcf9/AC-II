#include <detpic32.h>

void delay(int unsigned ms)
{
for ( ; ms > 0; ms--) 
	{
resetCoreTimer();
while (readCoreTimer() < 20000);
	}
}

void _int_(27) isr_adc(void)
{
int i;
int voltage;
int avg;
int *p = (int *) (&ADC1BUF0);
for(i = 0; i < 8; i++ ) {
avg = printInt((p[i*4]*33+511/1023), 10);
avg = (avg/8);
voltage = ((avg / 10) << 4) + (avg % 10));
AD1CON1bits.ASAM = 1;			// Start A/D conversion
IFS1bits.AD1IF = 0; 			// Reset AD1IF flag
}

global variable "voltage";
IFS1bits.AD1IF = 0;			// Reset AD1IF flag
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

volatile unsigned char voltage = 0; // Global variable
int main(void)
{
unsigned int cnt = 0;

static const char disp7Scodes[] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x77, 0x7C, 0x39, 0x5E, 0x79, 0x71};
unsigned char dh = disp7Scodes[value >> 4];      // Get the value at 7..4
unsigned char dl = disp7Scodes[value & 0x0F];    // Get the value at 3..0

TRISB = TRISB && 0x80FF;		// Configuring from RB14 - RB8
TRISD = TRISD && 0xFF9F;

TRISBbits.TRISB4 = 1; 			// RBx digital output disconnected
AD1PCFGbits.PCFG4= 0; 			// RBx configured as analog input
AD1CON1bits.SSRC = 7; 			// Conversion trigger selection bits: in this mode an internal counter ends sampling and 
					// starts conversion
AD1CON1bits.CLRASAM = 1; 		// Stop conversions when the 1st A/D converter interrupt is generated. At the same time, hardware
					// clears the ASAM bit
AD1CON3bits.SAMC = 16; 			// Sample time is 16 TAD (TAD = 100 ns)
AD1CON2bits.SMPI = 7; 			// Interrupt is generated after N samples (replace N by the desired number of consecutive samples)
AD1CHSbits.CH0SA = 4; 			// replace x by the desired input analog channel (0 to 15)
AD1CON1bits.ON = 1; 			// Enable A/D converter								
					
IFS1bits.AD1IF = 0; 			// clear A/D interrupt flag
IPC6bits.AD1IP = 2; 			// configure priority of A/D interrupts
IEC1bits.AD1IE = 1; 			// enable A/D interrupts
					// Configure interrupt system								
EnableInterrupts(); 			// Global Interrupt Enable
AD1CON1bits.ASAM = 1;			// Start conversion

EnableInterrupts(); 			// Global Interrupt Enable
while(1)
{

isr_adc();

if(cnt == 0) 				// 0, 200 ms, 400 ms, ... (5 samples/second)
{
AD1CON1bits.ASAM = 1;			// Start A/D conversion
}
					// Send "voltage" value to displays
cnt = (cnt + 1) % 20;
delay(10); 				// Wait 10 ms
}

send2displays(voltage);
return 0;
}
