/******************************************************************************
 * @file   : program.h
 * @project: DiceRollerC
 * @brief  : Provides menu data and handlers
 * @author : leifs
 ******************************************************************************/

#ifndef DICEROLLERC_PROGRAM_H
#define DICEROLLERC_PROGRAM_H

#include <stdint.h>
#include "lcd.h"
#include "ceresio.h"

typedef enum MenuEnum
{
    Splash,
    DieSelect,
    DieCount,
    DieMod,
    DieZero,
    DieAnim,
    DieTotal
} MenuEnum;

typedef enum ModEnum
{
    Reg,
    Adv,
    Dis
} ModEnum;

typedef struct ProgramState
{
    MenuEnum current_menu;
    bool is_rendered;
    uint8_t current_entry;
    uint8_t die_count;
    uint8_t die_sides;
    ModEnum die_mod;
    ButtonState buttons;
} ProgramState;

/**
 * @brief Clears the ProgramState for a new menu
 */
void reset_menu(void);

/**
 * @brief Splash screen
 */
void mSplash(void);

/**
 * @brief Die select screen
 */
void mDieSelect(void);

/**
 * @brief Die count screen
 */
void mDieCount(void);

/**
 * @brief Die modifier screen (advantage, disadvantage)
 */
void mDieMod(void);

/**
 * @brief Easter egg for having a custom Zero die
 */
void mDieZero(void);

/**
 * @brief Small waiting animation for suspense
 */
void mDieAnim(void);

/**
 * @brief Screen to display the total
 */
void mTotal(void);

#endif //DICEROLLERC_PROGRAM_H
