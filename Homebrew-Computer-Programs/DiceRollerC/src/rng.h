/******************************************************************************
 * @file   : rng.h
 * @project: DiceRollerC
 * @brief  : Provides RNG functions
 * @author : leifs
 ******************************************************************************/

#ifndef DICEROLLERC_RNG_H
#define DICEROLLERC_RNG_H

#include <stdint.h>

/**
 * @brief An implementation of xorshift. Internally 32 bit.
 * @return The 16-bit LSB of the xorshift state.
 */
uint16_t xorshift(void);

/**
 * @brief Simulates a dice roll
 * @param num Number of dice to roll
 * @param sides Number of sides for each die
 * @return Total
 */
uint16_t roll(uint8_t num, uint8_t sides);

/**
 * @brief Returns the maximum of a and b
 * @param a
 * @param b
 * @return The larger of the two parameters
 */
inline uint16_t max16(uint16_t a, uint16_t b)
{
    if(a > b) { return a; }
    return b;
}

/**
 * @brief Returns the minimum of a and b
 * @param a
 * @param b
 * @return The smaller of the two parameters
 */
inline uint16_t min16(uint16_t a, uint16_t b)
{
    if(a < b) { return a; }
    return b;
}

#endif //DICEROLLERC_RNG_H
