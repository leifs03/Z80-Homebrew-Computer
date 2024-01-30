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
        ++i;
    }
}



/**
 * @brief Converts an unsigned integer to an ASCII string
 * @param num Unsigned integer
 * @param str Pointer to string, at least 6 characters long.
 */
void uitoa(unsigned int num, char *str)
{
    int i = 0;

    // Handle the case when num is 0 separately
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return;
    }

    // Convert each digit of the number to ASCII and store in the string
    while (num != 0)
    {
        char digit = num % 10; // Extract the rightmost digit
        str[i++] = digit + '0'; // Convert digit to ASCII and store
        num /= 10; // Move to the next digit
    }

    str[i] = '\0'; // Null terminate the string

    // Reverse the string
    uint8_t start = 0;
    uint8_t end = i - 1;
    while(start < end)
    {
        char temp = str[start];
        str[start] = str[end];
        str[end] = temp;
        start++;
        end--;
    }
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
