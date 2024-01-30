/******************************************************************************
 * @file   : ceresio.c
 * @project: DiceRollerC
 * @brief  :
 * @author : leifs
*******************************************************************************/

#include "ceresio.h"
#include <stdlib.h>
#include "lcd.h"

__sfr __at(0x02) Buttons;

/**
 * @brief Prints a string to the LCD, unformatted
 * @param str
 */
void print(char* str)
{
    int i = 0;
    while(str[i] != '\0')
    {
        putchar(str[i]);
    }
}



/**
 * @brief Converts an unsigned integer to an ASCII string
 * @param uint Unsigned integer
 * @return Pointer to string, memory owned by caller
 */
char* uitoa(uint16_t uint)
{
    uint8_t str_size = numdigits(uint + 1);
    char* outstr = malloc(str_size);

    uint16_t value = uint;

    // Place null terminator
    outstr[str_size] = '\0';
    for(uint8_t i = 0; i < str_size; ++i)
    {
        char next_digit = (value % 10) + '0';
        value /= 10;
        outstr[str_size - i - 1] = next_digit;
    }

    return outstr;
}



/**
 * @brief Debounces and updates an existing ButtonState struct
 * @param button_state Pointer to state to update
 */
void readButtons(ButtonState* button_state)
{
    // Start with mask all pressed
    uint8_t debounced_read = 0x0F;

    // Debounce buttons by ANDing them with several other reads
    for(char i = 0; i < 5; i++)
    {
        uint8_t read = ~Buttons; // Buttons are inverted
        debounced_read &= read;
    }

    button_state->previous_state = button_state->current_state;
    button_state->current_state = debounced_read;

    button_state->l_pressed = (bool)((debounced_read >> 0) & 1);
    button_state->d_pressed = (bool)((debounced_read >> 1) & 1);
    button_state->u_pressed = (bool)((debounced_read >> 2) & 1);
    button_state->r_pressed = (bool)((debounced_read >> 3) & 1);

    // Check if button has changed state
    uint8_t diff = button_state->previous_state ^ debounced_read;

    button_state->l_changed = (bool)((diff >> 0) & 1);
    button_state->d_changed = (bool)((diff >> 1) & 1);
    button_state->u_changed = (bool)((diff >> 2) & 1);
    button_state->r_changed = (bool)((diff >> 3) & 1);
}



/**
 * @brief A simple value->digits calculation
 * @param value
 * @return A value between 0-5
 */
uint8_t numdigits(uint16_t value)
{
    // Poor man's log10 + 1
    if(value < 10) { return 1; }
    if(value < 100) { return 2; }
    if(value < 1000) { return 3; }
    if(value < 10000) { return 4; }
    return 5;
}
