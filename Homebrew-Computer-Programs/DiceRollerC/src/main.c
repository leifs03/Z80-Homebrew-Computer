/******************************************************************************
 * @file   : main.c
 * @project: DiceRollerC
 * @brief  : Handles the main program loop
 * @author : leifs
 ******************************************************************************/

#include <stdbool.h>
#include "lcd.h"
#include <stdio.h> // After lcd.h, since lcd provides getchar and putchar.

int main(void)
{
    lcd_init(true, false);

    printf("Hello, World!");

    return 0;
}
