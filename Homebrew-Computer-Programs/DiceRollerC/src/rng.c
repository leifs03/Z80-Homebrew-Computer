/******************************************************************************
 * @file   : rng.c
 * @project: DiceRollerC
 * @brief  : Provides RNG functions
 * @author : leifs
 ******************************************************************************/

#include "rng.h"
#include <stdint.h>

uint32_t rng_state = 0x3F3ECBF6; // Static random state

/**
 * @brief An implementation of xorshift. Internally 32 bit.
 * @return The 16-bit LSB of the xorshift state.
 */
uint16_t xorshift(void)
{
    uint32_t x = rng_state;

    x ^= x << 13;
    x ^= x >> 17;
    x ^= x << 5;

    rng_state = x;
    return x;
}

/**
 * @brief Sets the seed for xorshift
 * @param seed
 */
void seed(uint32_t seed)
{
    rng_state = seed;
}

/**
 * @brief Simulates a dice roll
 * @param num Number of dice to roll
 * @param sides Number of sides for each die
 * @return Total
 */
uint16_t roll(uint8_t num, uint8_t sides)
{
    uint16_t total = 0;
    for(uint8_t i = 0; i < num; i++)
    {
        total += (xorshift() % sides) + 1;
    }
    return total;
}

/**
 * @brief Rolls two dice with advantage
 * @param sides Number of sides for each die
 * @return The higher of two rolls
 */
uint8_t rollAdv(uint8_t sides)
{
    uint16_t roll1 = xorshift();
    uint16_t roll2 = xorshift();
    return max16(roll1, roll2);
}

/**
 * @brief Rolls two dice with disadvantage
 * @param sides Number of sides for each die
 * @return The lower of two rolls
 */
uint8_t rollDis(uint8_t sides)
{
    uint16_t roll1 = xorshift();
    uint16_t roll2 = xorshift();
    return min16(roll1, roll2);
}
