#include <detpic32.h>

void configUART(unsigned int baud, char parity, unsigned int dataBits, unsigned int stopbits){
    // Configure UART2:
    // 1 - Configure BaudRate Generator
    if (baud >= 600 || baud <= 115200){
        U2BRG = ((PBCLK + 8 * baud) / (16 * baud)) - 1;
    }
    else{
        U2BRG = 10;
    }

    
    if (dataBits < 8 || dataBits > 9)
    	dataBits = 8;
    	    
    if(dataBits == 8) {
    
	    if(parity == 'N')
	    {
		U2MODEbits.PDSEL = 00;   // 8 data bits and no parity
	    }
	    else if(parity == 'E')
	    {
		U2MODEbits.PDSEL = 01;   // 8 data bits and even parity
	    }
	    else if(parity == 'O')
	    {
		U2MODEbits.PDSEL = 10;   // 8 data bits and odd parity
	    }
	    
    if(dataBits == 9)
        U2MODEbits.PDSEL = 11;   // 9 data bits and no parity

    if(stopbits == 1 || stopbits == 2){
        U2MODEbits.STSEL = stopbits - 1;      // stop bits
    }
    else{
        U2MODEbits.STSEL = 0;      // 1 stop bit
    }
    U2MODEbits.BRGH = 0;       // divide by 16, 0 -> 16, 1 -> 4
    // 3 – Enable the trasmitter and receiver modules (see register U2STA)
    U2STAbits.URXEN = 1;       // 1 – Enable UART2 receiver (enables reception)
    U2STAbits.UTXEN = 1;       // 1 – Enable UART2 transmitter (enables trasmission)
    // 4 – Enable UART2 (see register U2MODE)
    U2MODEbits.ON = 1;         // 1 – Enable UART2 (enables UART2)

}
}

int main(void)
{
// Configure UART2: 115200, N, 8, 1

   configUART(115200, 'N', 8, 1);
   
					// Configure UART2 interrupts, with RX interrupts enabled
					//   and TX interrupts disabled:
IEC1bits.U2RXIE == 1;			//  enable U2RXIE
IEC1bits.U2TXIE == 0;			//  disable U2TXIE (register IEC1)

IPC8bits.U2IP == 1;			//   set UART2 priority level (register IPC8)
IFS1bits.U2RXIF == 0;			//   clear Interrupt Flag bit U2RXIF (register IFS1)
IEC1bits.U2RXIE == 1;			//   define RX interrupt mode (URXISEL bits)
					// Enable global Interrupts
					
while(1);

return 0;
}    

