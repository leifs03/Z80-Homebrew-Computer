/******************************************************************************
 * @file   : lcd.h
 * @project: DiceRollerC
 * @brief  : Handles LCD operations
 * @author : leifs
 ******************************************************************************/

#ifndef DICEROLLERC_LCD_H
#define DICEROLLERC_LCD_H

#include <stdbool.h>
#include <stdint.h>

/**
 * @brief Initializes the LCD
 * @param enable_cursor Show the cursor on screen
 * @param cursor_blink Have the cursor blink
 */
void lcd_init(bool enable_cursor, bool cursor_blink);

/**
 * @brief Clears the LCD and returns the cursor to 0,0
 */
void lcd_clear(void);

/**
 * @brief Moves the cursor to a given row and column
 * @param row Row, 0-1
 * @param col Column, 0-15
 */
void lcd_movcur(uint8_t row, uint8_t col);

/**
 * @brief Waits for the LCD to be ready
 * @warning Unexpectedly resets cursor position!
 */
void lcd_wait(void);

/**
 * @brief Displays a character on the LCD
 * @param c Character to print
 */
int putchar(int c);

#endif //DICEROLLERC_LCD_H
