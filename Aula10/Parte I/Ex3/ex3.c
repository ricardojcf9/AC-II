#include <detpic32.h>

void putstr(char *str);
void delay(unsigned int ms);

int main(void)
{
// Configure UART2 (115200, N, 8, 1)
    // 1 - Configure BaudRate Generator
    U2BRG = 10;                  		// ((20000000 + 8 * 115200) / (16 * 115200)) - 1;
   // 2 – Configure number of data bits, parity and number of stop bits
    						// (see U2MODE register)
    U2MODEbits.PDSEL = 0b00;   			// 8 data bits and no parity
    U2MODEbits.STSEL = 0;      			// 1 stop bit
    U2MODEbits.BRGH = 0;       			// divide by 16, 0 -> 16, 1 -> 4
   // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.URXEN = 1;      			// 1 – Enable UART2 receiver (enables reception)
    U2STAbits.UTXEN = 1;       			// 1 – Enable UART2 transmitter (enables trasmission)
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;        			// 1 – Enable UART2 (enables UART2)
    
while(1)
{
	putstr("String de teste\n");
	delay (1000);					// wait 1 s
}
return 0;
}


void putc(char byte)
{
while(U2STAbits.UTXBF == 1);			// wait while UART2 UTXBF == 1
U2TXREG = byte;					// Copy "byte" to the U2TXREG register
}

void putstr(char *str)
{
// use putc() function to send each charater ('\0' should not be sent)
while (*str != '\0')
{
putc(*str);
str++;
}
}

void delay(unsigned int ms) 
{
for (; ms > 0; ms--)
{
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}
