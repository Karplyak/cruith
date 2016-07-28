/*
lcdpcf8574 lib sample

copyright (c) Davide Gironi, 2013

Released under GPLv3.
Please refer to LICENSE file for licensing information.
*/


#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "onewire.h"
#include "ds18x20.h"


#include "lcdpcf8574/lcdpcf8574.h"

//#define UART_BAUD_RATE 2400
//#include "uart/uart.h"
unsigned char	nDevices;	// ���������� ��������
unsigned char	owDevicesIDs[MAXDEVICES][8];	// �� ID
unsigned char search_ow_devices(void) // ����� ���� ��������� �� ����
{
	unsigned char	i;
	unsigned char	id[OW_ROMCODE_SIZE];
	unsigned char	diff, sensors_count;

	sensors_count = 0;

	for( diff = OW_SEARCH_FIRST; diff != OW_LAST_DEVICE && sensors_count < MAXDEVICES ; )
	{
		OW_FindROM( &diff, &id[0] );

		if( diff == OW_PRESENCE_ERR ) break;

		if( diff == OW_DATA_ERR )	break;

		for (i=0;i<OW_ROMCODE_SIZE;i++)
		owDevicesIDs[sensors_count][i] = id[i];
		
		sensors_count++;
	}
	return sensors_count;

}
unsigned char	themperature[3]; // � ���� ������ ����� �������� �����������


int main(void)
{
	DDRC = 0b00000001; PORTC = 0b00000001;
	DDRB = 0b00000011;
	float t =0;
	
	//init uart
//	uart_init( UART_BAUD_SELECT(UART_BAUD_RATE,F_CPU) );
	char lcd_buf[16];
	sei();

	//init lcd
	lcd_init(LCD_DISP_ON_BLINK);
	_delay_ms(2);
	//lcd go home
	lcd_home();
	lcd_puts("Hello");

	uint8_t led = 0;
	nDevices = search_ow_devices(); // ���� ��� ����������

	while(1) {
		lcd_led(led); //set led
		led = !led; //invert led for next loop

		//test loop
		int i = 0;
		int line = 0;
		//for(i=0; i<10; i++) {
			char buf[10];
			itoa(i, buf, 10);
			lcd_gotoxy(0, line);
			//lcd_puts("i= ");
			
			//lcd_led(0);
			
			//lcd_gotoxy(3, line);
			//lcd_puts(buf);
			//line++;
			//line %= 2;
			//uart_puts(buf);
			//uart_puts("\r\n");
			_delay_ms(500);
			
			
			for (unsigned char i=0; i<nDevices; i++) // ������ �������� ���������� � ����������� ������
			{
				// ������ ���������� ����� �� ��� ��������� ����, ������� ���������� � ������ ����� �������
				switch (owDevicesIDs[i][0])
				{
					case OW_DS18B20_FAMILY_CODE: { // ���� ������ ����������� DS18B20
						//printf("\r"); print_address(owDevicesIDs[i]); // �������� ���� �������� ������, ����� - �����
						//printf(" - Thermometer DS18B20"); // �������� ��� ����������
						lcd_clrscr();
						sprintf(lcd_buf,"DS18B20=%1d", i+1);
						lcd_puts(lcd_buf);
						_delay_ms(800);
						DS18x20_StartMeasure(owDevicesIDs[i]); // ��������� ���������
						_delay_ms(800); // ���� ������� 750 ��, ���� �������������� �����������
						unsigned char	data[2]; // ���������� ��� �������� �������� � �������� ����� ������
						DS18x20_ReadData(owDevicesIDs[i], data); // ��������� ������
						lcd_clrscr();
						t = DS18x20_ConvertToThemperatureFl(data); // ��������������� ����������� � ���������������� ���
						//printf(": %3.2f C", t);
						//t=3.1;
						
						
						if (t<=80)
						{
							
							PORTB |= (1 << PB0);
							PORTB &= ~(1 << PB1);
						} 
						else
						{
							PORTB |= (1 << PB1);
							PORTB &= ~(1 << PB0);
						}
						 sprintf(lcd_buf,"T=%3.1f C", t);
						 lcd_puts(lcd_buf);
					} break;
					case OW_DS18S20_FAMILY_CODE: { // ���� ������ ����������� DS18B20
						//printf("\r"); print_address(owDevicesIDs[i]); // �������� ���� �������� ������, ����� - �����
						//printf(" - Thermometer DS18S20"); // �������� ��� ����������
						lcd_clrscr();
						lcd_puts("DS18B20t");
						_delay_ms(800);
					} break;

					case OW_DS1990_FAMILY_CODE: { // ���� ������ ����������� ���� DS1990
						//printf("\r"); print_address(owDevicesIDs[i]); // �������� ���� �������� ������, ����� - �����
						//printf(" - Serial button DS1990"); // �������� ��� ����������
						lcd_clrscr();
						lcd_puts("DS1990");
						_delay_ms(800);
					} break;
					case OW_DS2430_FAMILY_CODE: { // ���� ������� EEPROM
						//printf("\r"); print_address(owDevicesIDs[i]); // �������� ���� �������� ������, ����� - �����
						//printf(" - EEPROM DS2430"); // �������� ��� ����������
						lcd_clrscr();
						lcd_puts("EEPROM");
						_delay_ms(800);
					} break;
					case OW_DS2413_FAMILY_CODE: { // ���� ������ ����
						//printf("\r"); print_address(owDevicesIDs[i]); // �������� ���� �������� ������, ����� - �����
						//printf(" - Switch 2413"); // �������� ��� ����������
						lcd_clrscr();
						lcd_puts("key");
						_delay_ms(800);
					} break;
				}

			}

	//	}
	}
}


