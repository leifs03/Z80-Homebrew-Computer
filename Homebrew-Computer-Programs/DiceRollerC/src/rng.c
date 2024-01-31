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
 * @brief An implementation of xorshift+. Internally 32 bit.
 * @return The 16-bit LSB of the xorshift state.
 */
uint16_t xorshift(void)
{
    uint32_t x = rng_state;
    uint8_t s = (uint8_t)(x); // LSB of x
    x ^= x << 13;
    x ^= x >> 17;
    x ^= s ^ (x << 5);

    rng_state = x;
    return x + s;
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
        total += (sides - (xorshift() % (uint16_t)(sides)));
    }
    return total;
}
