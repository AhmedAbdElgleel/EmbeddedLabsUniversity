#include"lcd.h"
#include"uart.h"
#include"interrupt.h"
#include<util/delay.h>

void ISR_func(void);
uint8 ch = '0';

int main(){
	LCD_init();
	UART_init(9600);
	INT_CONF int_conf = {INT0_ID,RISING_EDGE};
	INT_init(&int_conf);
	INT_setISR(ISR_func,0);
	while(1);
}

void ISR_func(void){
	if('9' == ch)
	{
		ch = '0';
	}
	else{
		ch++;
	}

	UART_sendByte(ch);
	LCD_clearScreen();
	LCD_moveCursor(0,0);
	LCD_displayCharacter(ch);
	_delay_ms(500);
}
