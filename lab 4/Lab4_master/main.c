#include<avr/io.h>
#include<util/delay.h>
#include "spi.h"
#include "ext_interrupt_interface.h"
#include "std_types.h"
uint8 x = 65;
void callBackFunction(void)
{
	if(x>=122)
	{
		 x = 65;
	}
	else
	{
		x++;
	}
	SPI_sendReceiveByte(x);
	_delay_ms(500);
}

int main(void)
{
	SREG|=(1<<7);

	config spiConfig={RISING_FIRST,FIRST_EDGE,N_16,LSB};
	SPI_init_master(&spiConfig);

	Interrupt_Config intConfig={INT0_ID,FALLING_EDGE};
	INT_init(&intConfig);

	INT_setISR(SayedtQa2ed ,0);
	while(1)
	{

	}
}

