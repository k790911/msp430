#include <msp430.h> 
#include "myHeader.h"

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;	// stop watchdog timer

	int a;

	a = myAdder(2, 3);

	printf("%d\n", a);
}
