#ifndef _MENU_H_
#define _MENU_H_


#include "globals.h"
#include "keyboard.h"
#include "messages.h"
#include "lcd.h"

enum {
    MENU_CANCEL=1,
    MENU_RESET,
    MENU_MODE1,
    MENU_MODE2,
    MENU_MODE3,
    MENU_SENS1,
    MENU_SENS2,
    MENU_WARM,
    MENU_PROCESS
};
typedef const struct PROGMEM {
	const struct Menu_Item *Next; /**< Pointer to the next menu item of this menu item */
	const struct Menu_Item *Previous; /**< Pointer to the previous menu item of this menu item */
	const struct Menu_Item *Parent; /**< Pointer to the parent menu item of this menu item */
	const struct Menu_Item *Child; /**< Pointer to the child menu item of this menu item */
	//void (*SelectCallback)(void); /**< Pointer to the optional menu-specific select callback of this menu item */
	//void (*EnterCallback)(void); /**< Pointer to the optional menu-specific enter callback of this menu item */
	uint8_t     Select;
	const char Text[]; /**< Menu item text to pass to the menu display callback function */
} menuItem;

uint8_t startMenu();
void initMenu();

#endif
