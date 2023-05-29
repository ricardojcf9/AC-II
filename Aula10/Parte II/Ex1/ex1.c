#include <detpic32.h>

void configUART1(unsigned int baud, char parity, unsigned int dataBits, unsigned int stopbits);
void putc1(char byte);
char getc1(void);

int main(void)
{
configUART1(115200, 'N', 8, 1);
while(1)
{
char c = getc1();
putc1(c);
}
}


void configUART1(unsigned int baud, char parity, unsigned int dataBits, unsigned int stopbits)
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

void putc1(char byte)
{
while(U1STAbits.UTXBF == 1);			// wait while UART2 UTXBF == 1
U1TXREG = byte;					// Copy "byte" to the U2TXREG register
}

char getc1(void)
{
while (U1STAbits.URXDA == 0);			// Wait while URXDA == 0
return U1RXREG;					// Return U2RXREG
}
