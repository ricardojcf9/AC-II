#include <detpic32.h>

void delay(unsigned int ms)
{
for ( ; ms > 0; ms--) {
resetCoreTimer();
while (readCoreTimer() < 20000);
}
}

int main(void)
{

TRISE = TRISE & 0xFF87;
LATE = LATE & 0xFF87;

int counter = 0;

while (1) {
  delay(250);
  LATE = (LATE & 0xFF87) | (counter++ << 3);
  if (counter == 10)
  	counter = 0;

}
return 0;
}


