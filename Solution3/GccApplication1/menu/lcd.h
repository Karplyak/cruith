#ifndef _LCH_H_
#define _LCD_H_ 1

//#include "i2c_lcd.h"
/*
void lcd_write(unsigned char codeA)
{
	//cli();
	PORTB &= ~( _BV(LCD_A0) | _BV(LCD_RW) );
	_delay_us(10);
	PORTB |= _BV(LCD_E); // строб
	PORTB |= codeA; 
	_delay_us(10);
	PORTB &= ~_BV(LCD_E); // ~строб
	_delay_us(10);
	PORTB ^= codeA; 
	_delay_us(10);
	 //sei();
}

unsigned char lcd_readStatus()
{
	char BS;

	PORTB |= ( _BV(LCD_RW) );
	_delay_us(10);
	DDRB &= ~( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) );
	PORTB |= ( _BV(LCD_E) ); // строб
	_delay_us(10);
	PORTB &= ~_BV(LCD_E); // ~строб
	BS = (PORTA & _BV(LCD_DB7)) >> LCD_DB7;
	_delay_us(10);
	PORTB |= _BV(LCD_E); // строб
	_delay_us(10);
	PORTB &= ~_BV(LCD_E); // ~строб
	_delay_us(10);

	DDRB |= ( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) );
	PORTB &= ~( _BV(LCD_DB7) | _BV(LCD_DB6) | _BV(LCD_DB5) | _BV(LCD_DB4) | _BV(LCD_RW));
	_delay_us(2);

	return BS;
}

void lcd_putc(unsigned char ch)
{
	//while (lcd_readStatus()) {}

	lcd_write(_BV(LCD_A0) 
		| ((ch & _BV(7)) >> 7)	<< LCD_DB7
		| ((ch & _BV(6)) >> 6)	<< LCD_DB6
		| ((ch & _BV(5)) >> 5)	<< LCD_DB5
		| ((ch & _BV(4)) >> 4)	<< LCD_DB4
	);
	lcd_write(_BV(LCD_A0) 
		| ((ch & _BV(3)) >> 3)	<< LCD_DB7
		| ((ch & _BV(2)) >> 2)	<< LCD_DB6
		| ((ch & _BV(1)) >> 1)	<< LCD_DB5
		| (ch & 1) 		<< LCD_DB4
	);
	_delay_us(2);
}
*/

void lcd_clrscr(unsigned char data)
{
     unsigned char i = 0;
     if (data == 1)
     {
       i2c_lcd_gotoxy(0, 0);
	for (i=0; i<16; i++)
        	i2c_lcd_putch(' ');
        i2c_lcd_gotoxy(0, 0);
     }
     
     if (data == 2)
     {
        i2c_lcd_gotoxy(0, 1);
	for (i=0; i<16; i++)
        	i2c_lcd_putch(' ');
        i2c_lcd_gotoxy(0, 1);
     }
     
     if (data == 3)
     {
        /*Clear display*/
        i2c_lcd_clr();
        //_delay_us(120);         //Delay after clearing display
     }
}

#endif
