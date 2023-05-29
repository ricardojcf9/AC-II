#include <detpic32.h>

void configUART(unsigned int baud, char parity, unsigned int dataBits, unsigned int stopbits);
char getc(void);
void _int_(41) isr_uart2(void);

int main(void)
{


configUART(19200,'N', 8, 1);			// Configure UART2 (115200, N, 8, 1)

TRISCbits.TRISC14 = 0;				// config RC14 as output

while(1);

return 0;
}

void configUART(unsigned int baud, char parity, unsigned int dataBits, unsigned int stopbits)
{
	// Configure UART2:
    	// 1 - Configure BaudRate Generator
    				
   	if (baud >= 600 || baud <= 115200)
   	{
   	U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1;
   	}
   	else
   	{
   	U2BRG = 10;
   	}
   	
   	// 2 – Configure number of data bits, parity and number of stop bits
   	if (parity == 'N')
   	{
   	U2MODEbits.PDSEL == 0b00;
   	}
   	
   	else if (parity == 'E')
   	{
   	U2MODEbits.PDSEL == 0b01;
   	}
   	
   	else if (parity == 'O')
   	{
   	U2MODEbits.PDSEL == 0b10;
   	}
   	
   	else
   	{
   	U2MODEbits.PDSEL == 0b00;
   	}
   	
   	if (stopbits == 1 || stopbits == 2)
   	{
   	U2MODEbits.STSEL = stopbits-1;
   	}
   	
   	else
   	{
   	U2MODEbits.STSEL = 1;
   	}
   	
   	U2MODEbits.BRGH = 0;       // divide by 16, 0 -> 16, 1 -> 4
   	// 3 – Enable the trasmitter and receiver modules (see register U2STA)
    	U2STAbits.URXEN = 1;       // 1 – Enable UART2 receiver (enables reception)
    	U2STAbits.UTXEN = 1;       // 1 – Enable UART2 transmitter (enables trasmission)
   	// 4 – Enable UART2 (see register U2MODE)
   	U2MODEbits.ON = 1;         // 1 – Enable UART2 (enables UART2)

}

char getc(void)
{
while (U2STAbits.URXDA == 0);			// Wait while URXDA == 0
return U2RXREG;					// Return U2RXREG
}

void _int_(32) isr_uart2(void)
{
	if (IFS1bits.U2RXIF == 1)
	{
		char c = U2RXREG;				// Read character from FIFO (U2RXREG)
		
		if (c == 'T')
		{
		PORTCbits.RC14 = 1;
		}	
		else if(c == 't')
		{
		PORTCbits.RC14 = 0;
		}		
		
		IFS1bits.U2RXIF == 0;				// Clear UART2 Rx interrupt flag
	}
}

