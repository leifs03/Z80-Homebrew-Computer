/******************************************************************************
 * @file   : lcd.c
 * @project: DiceRollerC
 * @brief  : Handles LCD operations
 * @author : leifs
 ******************************************************************************/

#include "lcd.h"
#include <stdbool.h>
#include <stdint.h>

__sfr __at(0x00) LCDReg;
__sfr __at(0x01) LCDRam;

const uint8_t LCDFunctionSet = 0b00111000; // 8-bit, 16x2 chars, 5x8 font
const uint8_t LCDClearScreen = 0b00000001;
const uint8_t LCDEntrySet = 0b00000110; // Increment on print, no shift
const uint8_t LCDReturnHome = 0b00000010;
const uint8_t LCDDisplaySet = 0b00001100; // b0 : blink, b1 : cursor
const uint8_t LCDSetCursorAddress = 0b10000000; // b0-7 : new address

/**
 * @brief Delays long enough for the LCD to process without resetting cursor
 */
void lcd_delay(void)
{
    // Busy wait... Compiler decided to use IY so this is enough, actually.
    for(volatile char i = 0; i < 1; ++i);
}



/**
 * @brief Initializes the LCD
 * @param enable_cursor Show the cursor on screen
 * @param cursor_blink Have the cursor blink
 */
void lcd_init(bool enable_cursor, bool cursor_blink)
{
    uint8_t display_set_full = LCDDisplaySet; // Need to add on parameters

    // Extra long delay for LCD controller to run through its own startup
    for(char i = 0; i < 5; ++i)
    {
        lcd_delay();
    }

    // Have to set function twice, per the datasheet
    LCDReg = LCDFunctionSet;
    lcd_delay();
    LCDReg = LCDFunctionSet;
    lcd_delay();

    if(enable_cursor) { display_set_full |= 0b0010; }
    if(cursor_blink) { display_set_full |= 0b0001; }
    LCDReg = display_set_full;
    lcd_wait();

    LCDReg = LCDClearScreen;
    lcd_wait();

    LCDReg = LCDEntrySet;
    lcd_wait();
}



/**
 * @brief Clears the LCD and returns the cursor to 0,0
 */
void lcd_clear(void)
{
    LCDReg = LCDClearScreen;
    lcd_wait();
}



/**
 * @brief Returns the cursor to 0,0
 */
void lcd_rethome(void)
{
    LCDReg = LCDReturnHome;
    lcd_wait();
}



/**
 * @brief Moves the cursor to a given row and column
 * @param row Row, 0-1
 * @param col Column, 0-15
 */
void lcd_movcur(uint8_t row, uint8_t col)
{
    uint8_t address = col;
    if(row == 1) { address += 0x40; } // Start of second row in LCD memory
    LCDReg = LCDSetCursorAddress | address;
    lcd_delay();
}



/**
 * @brief Waits for the LCD to be ready
 * @warning Unexpectedly resets cursor position!
 */
void lcd_wait(void)
{
    uint8_t lcd_status;
    bool lcd_busy;

    do
    {
        lcd_delay();
        lcd_status = LCDReg;
        lcd_busy = (lcd_status >> 7) & 1;
    } while(lcd_busy);
}



/**
 * @brief Displays a character on the LCD
 * @param c Character to print
 */
int putchar(int c)
{
    lcd_delay();
    LCDRam = c;
    return 0;
}
