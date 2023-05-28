#include <detpic32.h>

volatile int voltage = 0;			// Global variable


void delay(int ms);
void send2displays(unsigned char value);
int voltageConversion(int value);
void configureAll();

int main(void)
{
	configureAll(); 			// Function to configure all (digital I/O, analog)
	
	    					// Reset AD1IF, T1IF and T3IF flags 
    	IFS1bits.AD1IF = 0; 			// Reset AD1IF flag
    	IFS0bits.T2IF = 0; 			// Reset timer T2 interrupt flag
        IFS0bits.T3IF = 0; 			// Reset timer T3 interrupt flag
						
EnableInterrupts();				// Global Interrupt Enable
while(1);
return 0;
}

void configureAll(void)
{

	TRISB = TRISB & 0x80FF;			// Configure RB8 to RB14 as outputs
	TRISD = TRISD & 0xFF9F;			// Configure RD5 to RB6 as outputs
	
						// input, A/D module, timers T1 and T3, interrupts)
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
											
						// Configure Timer1
	T1CONbits.TCKPS = 2; 			// 1:64 prescaler 
    	PR1 = 62499; 				// Fout = 20MHz / (64 * (62499 + 1)) = 5 Hz
   	TMR1 = 0; 				// Clear timer T1 count register
  	T1CONbits.TON = 1; 			// Enable timer T1 
  	
  						// Configure Timer3
	T3CONbits.TCKPS = 2; 			// 1:64 prescaler 
    	PR3 = 49999; 				// Fout = 20MHz / (64 * (62499 + 1)) = 5 Hz
   	TMR3 = 0; 				// Clear timer T1 count register
  	T3CONbits.TON = 1; 			// Enable timer T1 
  	
  	IPC6bits.AD1IP = 2; 			// configure priority of A/D interrupts
    	IEC1bits.AD1IE = 1; 			// enale A/D interrupts
    	IPC1bits.T1IP = 1; 			// Interrupt priority (must be in range [1..6])
    	IEC0bits.T1IE = 1; 			// Enable timer T1 interrupts 
    	IPC3bits.T3IP = 3; 			// Interrupt priority (must be in range [1..6])
   	IEC0bits.T3IE = 1; 			// Enable timer T3 interrupts
  	
						
}

void _int_(4) isr_T1(void)
{
AD1CON1bits.ASAM = 1;// Start A/D conversion
IFS0bits.T1IF = 0;// Reset T1IF flag
}

void _int_(12) isr_T3(void)
{
voltage = (voltage * 33 + 511) / 1023;
send2displays(voltage);
IFS0bits.T3IF = 0;// Reset T3IF flag
}

void _int_(27) isr_adc(void)
{
						// Calculate buffer average (8 samples)
int sum = 0;
int i = 0;
int *p = (int *)&ADC1BUF0;
for(i = 0; i < 8; i++)
{
sum += p[i * 4];
						// Calculate voltage amplitude and copy it to "voltage"
voltage = sum / 8;
voltage = voltageConversion(voltage);

}
IFS1bits.AD1IF = 0;				// Reset AD1IF flag
}

void delay(int ms)
{
for (; ms > 0; ms--)
{
resetCoreTimer();
while(readCoreTimer() < 20000);
}
}

void send2displays(unsigned char value)
{
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

int voltageConversion(int value)
{
    return (value * 33 + 511) / 1024;
}
