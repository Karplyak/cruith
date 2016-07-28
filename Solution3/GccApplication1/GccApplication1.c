/*
 * GccApplication1.c
 *
 * Created: 04.01.2016 22:52:03
 *  Author: MUSTANG
 */ 

#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <util/delay.h>

#include "i2cmaster.h"
#include "i2c_lcd.h"
#include "lcd.h"
#include "MicroMenu.h"
//#include "menu/keyboard.h"

char data[16], time[21];
int j=0, t1=101, men = 0;
int i=0;
int stm=0;

/*** DUMY CODE ***/
static void Level1Item1_Enter(void);
static void Level1Item1_Select(void);
enum ButtonValues
{
	BUTTON_NONE,
	BUTTON_UP,
	BUTTON_DOWN,
	BUTTON_LEFT,
	BUTTON_RIGHT,
	BUTTON_ENTER,
};

/** Example menu item specific enter callback function, run when the associated menu item is entered. */
static void Level1Item1_Enter(void)
{
	i2c_lcd_puts("ENTER1");
}

static void Level1Item1_Select(void)
{
	men=1;
}
static void Level2Item1_Select(void)
{
	men=2;
}
static void Level3Item1_Select(void)
{
	men=3;
}
static void Level4Item1_Select(void)
{
	men=4;
}
static void Level5Item1_Select(void)
{
	men=5;
}
static void Level6Item1_Select(void)
{
	men=6;
}

 void viewmenu()
{
	switch(men)
	{
		case 0:
		
		break;
		
		case 1:
		lcd_clrscr(2);
		i2c_lcd_gotoxy(0,1);
		 sprintf(data,"M=%d t=%d",men,t1);
		i2c_lcd_puts(data);
		//_delay_ms(2000);
		break;
		
		case 2:
		lcd_clrscr(2);
		i2c_lcd_gotoxy(0,1);
		sprintf(data,"M=%d t=%d",men,t1);
		i2c_lcd_puts(data);
		//_delay_ms(2000);
		break;
		
		case 3:
		lcd_clrscr(2);
		i2c_lcd_gotoxy(0,1);
		sprintf(data,"M=%d t=%d",men,t1);
		i2c_lcd_puts(data);
		//stepm(10);
		break;
		
		case 4:
		lcd_clrscr(2);
		i2c_lcd_gotoxy(0,1);
		sprintf(data,"M=%d t=%d",men,t1);
		i2c_lcd_puts(data);
		//_delay_ms(2000);
		break;
		case 5:
		lcd_clrscr(2);
		i2c_lcd_gotoxy(0,1);
		sprintf(data,"M=%d t=%d",men,t1);
		i2c_lcd_puts(data);
		//_delay_ms(2000);
		break;
	}
}

/** Example menu item specific select callback function, run when the associated menu item is selected. */
void stepm(int kr)
{	//unsigned char step[] = {0b00000001, 0b00000010, 0b00000100};
		if (kr==0) //зменшення газу до 0
		{
			do 
			{
				switch(stm)
				{
					case 0:
					//PORTC = step[0];
					PORTC = (0<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
					stm++;
					break;
					
					case 1:
					//PORTC = step[1];
					PORTC = (0<<PORTC2)|(1<<PORTC1)|(0<<PORTC0);
					stm++;
					break;
					
					case 2:
					//PORTC = step[2];
					PORTC = (1<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
					stm=0;
					break;
				}
			} while ((PINB & (1<<PINB5)) !=0);///////////////////////////////////////////////////////////////////////
		} 
		else
	{
			if (kr>0) //газувати
		{			
			for (int i=0; i < kr; i++)
			{ 
				if ((PINB & (1<<PINB5)) !=0)/////////////////////////////////////////////////////////////////
			 {
					switch(stm)
				{
					case 0:
					//PORTC = step[0];
					PORTC = (0<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
					stm++;
					break;
			
					case 1:
					//PORTC = step[1];
					PORTC = (0<<PORTC2)|(1<<PORTC1)|(0<<PORTC0);
					stm++;
					break;
			
					case 2:
					//PORTC = step[2];
					PORTC = (1<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
					stm=0;
					break;
				}		
			 }
			}

		} else //тормозити
			{
		for (int i=0; i < kr; i++)
		{	
			if ((PINB & (1<<PINB5)) !=0) //////////////////////////////////////////////////
		{
			switch(stm)
			{
				case 2:
				//PORTC = step[0];
				PORTC = (0<<PORTC2)|(0<<PORTC1)|(1<<PORTC0);
				stm++;
				break;
				
				case 1:
				//PORTC = step[1];
				PORTC = (0<<PORTC2)|(1<<PORTC1)|(0<<PORTC0);
				stm++;
				break;
				
				case 0:
				//PORTC = step[2];
				PORTC = (1<<PORTC2)|(0<<PORTC1)|(0<<PORTC0);
				stm=0;
				break;
			}
		}
		}
			}
			
	}
	
}

/** Generic function to write the text of a menu.
 *
 *  \param[in] Text   Text of the selected menu to write, in \ref MENU_ITEM_STORAGE memory space
 */
static void Generic_Write(const char* Text)
{
	if (Text)
		i2c_lcd_puts(Text);
		else
		{
			i2c_lcd_puts("NO Text");
		}
		//_delay_ms(2000);
}
//MENU_ITEM(Name, Next, Previous, Parent, Child, SelectFunc, EnterFunc, Text)
MENU_ITEM(Menu_1, Menu_2, Menu_2, NULL_MENU, Menu_1_1,  Level1Item1_Select, Level1Item1_Enter, "Start");
MENU_ITEM(Menu_2, Menu_1, Menu_1, NULL_MENU, Menu_2_1, Level2Item1_Select, NULL, "MENU");
//MENU_ITEM(Menu_3, Menu_1, Menu_2, NULL_MENU, NULL_MENU, Level3Item1_Enter, NULL, "MENU3");

MENU_ITEM(Menu_1_1, Menu_1_2, Menu_1_2, Menu_1, NULL_MENU, Level3Item1_Select, NULL, "Rezhum 1");
MENU_ITEM(Menu_1_2, Menu_1_1, Menu_1_1, Menu_1, NULL_MENU, Level4Item1_Select, NULL, "Rezhum 2");

MENU_ITEM(Menu_2_1, Menu_1_2, Menu_1_2, Menu_2, NULL_MENU, Level5Item1_Select, NULL, "Oborotu");
MENU_ITEM(Menu_2_2, Menu_1_1, Menu_1_1, Menu_2, NULL_MENU, Level6Item1_Select, NULL, "Tochnist");

/*MENU_ITEM(Menu_3_1, Menu_1_2, Menu_1_2, Menu_3, NULL_MENU, Level8Item1_Enter, NULL, "MENU3.1");
MENU_ITEM(Menu_3_2, Menu_1_1, Menu_1_1, Menu_3, NULL_MENU, Level9Item1_Enter, NULL, "MENU3.2");*/

enum ButtonValues GetButtonPress(void)
{	
	//return BUTTON_NONE;
	//return readKey();
	uint8_t ah=PINB;
		if (!(ah & _BV(4))) {
			return BUTTON_ENTER;
		}
		if (!(ah & _BV(1))) {
			return BUTTON_UP;
		}
		if (!(ah & _BV(2))) {
			return BUTTON_DOWN;
		}
		if (!(ah & _BV(3))) {
			return BUTTON_LEFT;
		}
		if (!(ah & _BV(0))) {
			return BUTTON_RIGHT;
		}
		return 0;
};
/*** END DUMY CODE ***/


ISR (INT0_vect) //переход на следующий режим при ажатии кнопки
{ 
	cli();//запрещение прерываний на время обработки прерывания
	j++;
	sei();//разрешение прерываний
 }

ISR (TIMER1_COMPA_vect) //переход на следующий режим при ажатии кнопки
{ 
	cli();//запрещение прерываний на время обработки прерывания
	 t1++; 
	//TCNT1 = 0xFD8F;
	 if( PIND & ( 1 << PD0 ) ) {
    PORTD &= ~( 1 << PD0 );
  }
  else {
    PORTD |= ( 1 << PD0 );
  }
  if( t1>10 ) {
	  t1=0;
	 lcd_clrscr(1);
	  i2c_lcd_gotoxy(0,0);
	   sprintf(data,"J=%d t=%d",j,t1);
	   i2c_lcd_puts(data); 
	 // _delay_ms(200);
  }
  int bzn = 60; //=2000
  int r1 =j-bzn;
  j=0;
  //3,10,30 
  if ((r1>=3) &&(r1<10))  {stepm(-50);}
  if ((r1>=10)&&(r1<30))  {stepm(-100);}
  if ((r1>=30))  {stepm(-250);}
 
  if ((r1>=-3) &&(r1<-10))  {stepm(50);}
  if ((r1>=-10)&&(r1<-30))  {stepm(100);}
  if ((r1>=-30)&&(r1<-45))  {stepm(250);}
  if ((r1>=45))  {stepm(0);}
	sei();//разрешение прерываний
}

unsigned char dispMenu() {
	Menu_Item_t* tempMenu;

	lcd_clrscr(1);
	// первая строка - заголовок. Или пункт меню верхнего уровня
	i2c_lcd_gotoxy(1,0);
	tempMenu = (Menu_Item_t*)pgm_read_word(&Menu_GetCurrentMenu()->Parent);
	if ((void*)tempMenu == (void*)&NULL_MENU) { // мы на верхнем уровне
		i2c_lcd_puts("MENU:");
		//i2c_lcd_puts((char*)CurrentMenuItem->Text);
		
		if (Menu_GetCurrentMenu() == &Menu_1) i2c_lcd_puts("Menu_1");
		if (Menu_GetCurrentMenu() == &Menu_2) i2c_lcd_puts("Menu_2");
		if (Menu_GetCurrentMenu() == &Menu_1_1) i2c_lcd_puts("Menu_1_1");
		if (Menu_GetCurrentMenu() == &Menu_1_2) i2c_lcd_puts("Menu_1_2");
		if (Menu_GetCurrentMenu() == &Menu_2_1) i2c_lcd_puts("Menu_2_1");
		if (Menu_GetCurrentMenu() == &Menu_2_2) i2c_lcd_puts("Menu_2_2");
		//if (Menu_GetCurrentMenu() == &Menu_3_1) i2c_lcd_puts("Menu_3_1");
		//if (Menu_GetCurrentMenu() == &Menu_3_2) i2c_lcd_puts("Menu_3_2");
		
		} else {
		i2c_lcd_puts(tempMenu->Text);
	}

	lcd_clrscr(2);
	// Вторая строка - текущий пункт меню
	i2c_lcd_gotoxy(2,1);
	i2c_lcd_puts((char *)Menu_GetCurrentMenu()->Text);

	return (1);
}

int main(void)
{
	DDRC = 0b00000111; // DDRB >> 1-out, 0-in
	DDRB = 0b00000000; // DDRB >> 1-out, 0-in
	DDRD = 0b00000011;
	PORTB = 0b00011111;
	PORTC = 0b00100000;
	PORTD = 0b00000010;
	
		//KBD_init();
	i2c_lcd_init();//инициализация LCD
	i2c_lcd_clr();
	i2c_lcd_gotoxy(0,0);
	//i2c_lcd_puts("i2c I/O expander");
	//_delay_ms(2500);
	
	//char light = 0;
	
	
	// TIMSK0 = 0x00; // timer interrupt sources
	 EIMSK= (1<<INT0)|(1<<INT1); //разрешение прерывания на INT0
	 MCUCR |=(1<<ISC01)|(1<<ISC00); //регистр настройки прерываний на выводах INT0 и INT1
	 
	 
	 TCCR1B = (0<<CS12)|(1<<CS11)|(0<<CS10);
	 //TCNT1 = 0xFD8F;
	 OCR1A =0x4E20;
	 TIMSK1=(1<<OCIE1A);
	 sei();
	 
	 //
	 	/* Set up the default menu text write callback, and navigate to an absolute menu item entry. */
	Menu_SetGenericWriteCallback(Generic_Write);
	Menu_Navigate(&Menu_1);
	 
	 //
    while(1)
    {	//switch (readKey())
		switch (GetButtonPress())
	    {
		    case BUTTON_UP:
			i2c_lcd_puts("up");
		    Menu_Navigate(MENU_PREVIOUS);
			//_delay_ms(2000);
		    break;
		    case BUTTON_DOWN:
			i2c_lcd_puts("down");
		    Menu_Navigate(MENU_NEXT);//_delay_ms(2000);
		    break;
		    case BUTTON_LEFT:
			i2c_lcd_puts("left");
		    Menu_Navigate(MENU_PARENT);//_delay_ms(2000);
		    break;
		    case BUTTON_RIGHT:
			i2c_lcd_puts("right");
		    Menu_Navigate(MENU_CHILD);//_delay_ms(2000);
		    break;
		    case BUTTON_ENTER:
			i2c_lcd_puts("enter");
		    Menu_EnterCurrentItem();//_delay_ms(2000);
		    break;
		    default:
		    {/*i2c_lcd_clr();dispMenu();*/
				i2c_lcd_puts(Menu_GetCurrentMenu()->Text);
			 //   Level1Item1_Enter();
			  //  Level1Item1_Select();
			  
				
		    }
		    break;
	    }
		
		
		viewmenu();
		
		
		
		i2c_lcd_gotoxy(0,0);
		// sprintf(data,"J=%d t=%d",j,t1);
		// i2c_lcd_puts(data);
		 _delay_ms(2000);
		
		/*if((PIND & (1<<PIND1))==1) {PORTD = 0b00000000;} else {PORTD = 0b00000010;}
	
		
		 if((PINB & (1<<PINB0)) == 0) //If switch is pressed
		 {
			
			 PORTD |= (1<<PIND0); //Turns ON LED
		//	 lcd_light(LCD_BACKLIGHT_OFF);
			 _delay_ms(200); //3 second delay
			// PORTC &= ~(1<<PC0); //Turns OFF LED
			if(light==1)
			{//lcd_init(LCD_BACKLIGHT_ON);
			//	lcd_puts_P(PSTR("Y:"));
				light = 0;
				//lcd_light(LCD_BACKLIGHT_ON);
			} else {
				//lcd_light(LCD_BACKLIGHT_OFF);
				//lcd_puts_P(PSTR("X:"));
				light = 1;
				 //PORTD = 0;
			}
			
		 }
		
	
		if((PINB & (1<<PINB1)) == 0) //If switch is pressed
		{
			i2c_lcd_clr();
			i2c_lcd_gotoxy(0,0);
			sprintf(data,"I=%d",i);
			i2c_lcd_puts(data); 
			_delay_ms(200);
			
			switch(i)
			{
				case 0:
				PORTC = step[0];
				i++;
				break;
				case 1:
				PORTC = step[1];
				i++;
				break;
				case 2:
				PORTC = step[2];
				i=0;
				break;
			}
			
		}*/
    }
}
	