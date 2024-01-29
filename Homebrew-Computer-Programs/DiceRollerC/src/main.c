/******************************************************************************
 * @file   : main.c
 * @project: DiceRollerC
 * @brief  : Handles the main program loop
 * @author : leifs
 ******************************************************************************/

#include <stdio.h>
#include <stdbool.h>
#include "lcd.h"

int main(void)
{
    lcd_init(false, true);

    puts("Hello, World!   "); // Puts appends \n, even though that doesn't work.

    return 0;
}
