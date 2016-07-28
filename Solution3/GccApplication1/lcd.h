
#include <avr/io.h>
#include <util/delay.h>

#define PORT_LCD PORTC	
#define DDR_LCD DDRC

/* ��������� ���. "1" �� ����� E */
#define LCD_E_SET    PORT_LCD |=0x02
/* ��������� ���. "0" �� ����� E */
#define LCD_E_CLR    PORT_LCD &=0xFD
/* ��������� ���. "1" �� ����� RS */
#define LCD_RS_SET   PORT_LCD|=0x01
/* ��������� ���. "0" �� ����� RS */
#define LCD_RS_CLR   PORT_LCD&=0xFE

/* ������, ����������� �������, ���
���������� ������� */
#define LCD_COMMAND  0
/* ������, ����������� �������, ���
���������� ������ */
#define LCD_DATA     1


#define lcd_putc(x)  lcd_putbyte(x, LCD_DATA)


/* ������������� ������,
������������ � ��� */
void init_port()
{
	PORT_LCD=0x00;
    DDR_LCD=0xFF;
}

/* ������� �������� ������� � ��� */
/*void lcd_putnibble(char t)
{
    t<<=4;
    //LCD_E_SET;
    _delay_us(50);
    //Led_port&=~0xF0;
   // I2C_SendPocket (Led_port|t);
   // LCD_E_CLR;
    _delay_us(50);
}

 ������� �������� ����� � ���.
char c - ��� ����
char rs - ����������, ����������� ��� ����������:
     rs = 0 - ������� (��������������� ����� RS)
	 rs = 1 - ������ (������������ ����� RS) */
/*void lcd_putbyte(char c, char rs)
{
    char highc=0;
    highc=c>>4;
	if (rs==LCD_COMMAND) LCD_RS_CLR;
	else                 LCD_RS_SET;
    lcd_putnibble(highc);
    lcd_putnibble(c);
}

void lcd_putchar(char c)
{
    char highc=0;
    highc=c>>4;
	LCD_RS_SET;
    lcd_putnibble(highc);
    lcd_putnibble(c);
}*/

/* ������� ������������� ������ ���
� 4-������ ������, ��� ������� 
void lcd_init()
{
    _delay_ms(15);
    lcd_putnibble(0b00000011);
    _delay_ms(4);
    lcd_putnibble(0b00000011);
    _delay_us(100);
    lcd_putnibble(0b00000011);
	 _delay_ms(1);
    lcd_putnibble(0b00000010);
	_delay_ms(1);
    lcd_putbyte(0x28, LCD_COMMAND); // ����� (0x28) 5x8 0b00101000 ������ (0x2C) 5x10 0b00101100 
    _delay_ms(1);
    lcd_putbyte(0x0C, LCD_COMMAND);
    _delay_ms(1);
    lcd_putbyte(0x06, LCD_COMMAND);
    _delay_ms(1);
}*/


/* ������� ������� ������� � ��������
������� � ��������� �������
void lcd_clear()
{
    lcd_putbyte(0x01, LCD_COMMAND);
    _delay_us(1500);
}*/



/* ������� ����������� ������� � �������� �������
col - ����� ���������� �� �������������� ��� (�� 0 �� 15)
row - ����� ������ (0 ��� 1) 
void lcd_gotoxy(char col, char row)
{
  char adr;
  adr=0x40*row+col;
  adr|=0x80;
  lcd_putbyte(adr, LCD_COMMAND);
}*/
/*
void lcd_putstring (char stroka[])
{  char i;
   for(i=0;stroka[i]!='\0';i++)
   lcd_putchar(stroka[i]);
}*/	