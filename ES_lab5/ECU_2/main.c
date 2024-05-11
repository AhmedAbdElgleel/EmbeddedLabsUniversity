#include"lcd.h"
#include"uart.h"

uint8 ch = '0';

int main(){
	LCD_init();
	UART_init(9600);
	while(1){
		ch = UART_recieveByte();
		LCD_clearScreen();
		LCD_moveCursor(0,0);
		LCD_displayCharacter(ch);
	}
}
