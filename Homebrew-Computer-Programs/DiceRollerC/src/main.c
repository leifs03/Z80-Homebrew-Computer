/******************************************************************************
 * @file   : main.c
 * @project: DiceRollerC
 * @brief  : Handles the main program loop
 * @author : leifs
 ******************************************************************************/

#include <stdlib.h>
#include <stdbool.h>
#include "lcd.h"
#include "ceresio.h"
#include "rng.h"

int main(void)
{
    lcd_init(false, true);

    while(true)
    {
        char* roll = uitoa(xorshift());
        print(roll);
        free(roll);

        // Busy loop
        for(volatile uint16_t i = 0; i < 65535; i++);

        lcd_clear();
    }

    return 0;
}
