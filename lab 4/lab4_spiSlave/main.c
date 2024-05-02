#include<avr/io.h>
#include<util/delay.h>
#include "spi.h"
#include "lcd.h"
#include "std_types.h"
#include "common_macros.h"

int main(void)
{
	uint8 dummy_varibale;

	LCD_init();

	config spiConfig={RISING_FIRST,FIRST_EDGE,N_16,LSB};
	SPI_init_slave(&spiConfig);

	while(1)
	{
		uint8 received=SPI_sendReceiveByte(dummy_varibale);
		LCD_moveCursor(0,0);
		LCD_clearScreen();
		LCD_intgerToString(received);
		_delay_ms(50);
	}
}

