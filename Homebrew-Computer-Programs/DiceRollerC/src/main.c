/******************************************************************************
 * @file   : main.c
 * @project: DiceRollerC
 * @brief  : Handles the main program loop
 * @author : leifs
 ******************************************************************************/

#include <stdbool.h>
#include "lcd.h"
#include "ceresio.h"

int main(void)
{
    lcd_init(false, true);

    print("Hello, World!");

    return 0;
}
