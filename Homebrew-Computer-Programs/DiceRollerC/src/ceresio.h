/******************************************************************************
 * @file   : ceresio.h
 * @project: DiceRollerC
 * @brief  : Provides limited standard library and IO functions.
 * @author : leifs
*******************************************************************************/

#ifndef DICEROLLERC_CERESIO_H
#define DICEROLLERC_CERESIO_H

#include <stdint.h>
#include <stdbool.h>

typedef struct ButtonState
{
    uint8_t previous_state;
    uint8_t current_state;
    bool l_pressed : 1;
    bool l_changed : 1;
    bool d_pressed : 1;
    bool d_changed : 1;
    bool u_pressed : 1;
    bool u_changed : 1;
    bool r_pressed : 1;
    bool r_changed : 1;
} ButtonState;

/**
 * @brief Prints a string to the LCD, unformatted
 * @param str
 */
void print(char* str);

/**
 * @brief Converts an unsigned integer to an ASCII string
 * @param num Unsigned integer
 * @param str Pointer to string, at least 6 characters long.
 */
void uitoa(unsigned int num, char *str);

/**
 * @brief Debounces and updates an existing ButtonState struct
 * @param button_state Pointer to state to update
 */
void readButtons(ButtonState* button_state);

/**
 * @brief A simple value->digits calculation
 * @param value
 * @return A value between 0-5
 */
uint8_t numdigits(uint16_t value);

#endif //DICEROLLERC_CERESIO_H
