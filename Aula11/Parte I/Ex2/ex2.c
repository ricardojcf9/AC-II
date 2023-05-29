#include <detpic32.h>

void _int_(41) isr_uart2(void)
{
	if (IFS1bits.U2RXIF == 1)
	{
		char c = U2RXREG;				// Read character from FIFO (U2RXREG)
		putc(c);					// Send the character using putc()
		IFS1bits.U2RXIF == 0;				// Clear UART2 Rx interrupt flag
	}
}

void putc(char byte)
{
	while(U2STAbits.UTXBF == 1);				// wait while UART2 UTXBF == 1
	U2TXREG = byte;						// Copy "byte" to the U2TXREG register
}
